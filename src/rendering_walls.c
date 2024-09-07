/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:06:30 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 04:57:36 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*select_txtr(t_graphics *graf, int texture)
{
	graf->raycast->beam_angle = quantum_phase_shift(graf->raycast->beam_angle);
	if (texture == 0)
	{
		if (graf->raycast->beam_angle > M_PI / 2
			&& graf->raycast->beam_angle < 3 * (M_PI / 2))
			return (graf->texture->ea);
		else
			return (graf->texture->we);
	}
	else
	{
		if (graf->raycast->beam_angle > 0 && graf->raycast->beam_angle < M_PI)
			return (graf->texture->so);
		else
			return (graf->texture->no);
	}
}

void	fill_floor_and_ceiling(t_graphics *gfx, int ray_index, int top_pixel,
		int bottom_pixel)
{
	int	current_pixel;
	int	floor_color;
	int	ceiling_color;

	floor_color = (ft_atoi(gfx->data->floor_clr[0]) << 24 | ft_atoi(gfx->data->floor_clr[1]) << 16 | ft_atoi(gfx->data->floor_clr[2]) << 8 | 255);
	ceiling_color = (ft_atoi(gfx->data->ceiling_clr[0]) << 24 | ft_atoi(gfx->data->ceiling_clr[1]) << 16 | ft_atoi(gfx->data->ceiling_clr[2]) << 8 | 255);
	current_pixel = bottom_pixel;
	while (current_pixel < HEIGHT)
		place_pixel(gfx, ray_index, current_pixel++, floor_color);
	current_pixel = 0;
	while (current_pixel < top_pixel)
		place_pixel(gfx, ray_index, current_pixel++, ceiling_color);
}

double	calculate_euclidean_norm(mlx_texture_t *texture, t_graphics *graf)
{
	double	offset_x;

	if (graf->raycast->hit_type == 1)
		offset_x = (int)fmodf((graf->raycast->intrsxn_x_horz * (texture->width
						/ MAP_BLOCK_LEN)), texture->width);
	else
		offset_x = (int)fmodf((graf->raycast->intrsxn_y_vert * (texture->width
						/ MAP_BLOCK_LEN)), texture->width);
	return (offset_x);
}

void	place_pixel(t_graphics *graphics, int pos_x, int pos_y, int color_value)
//
{
	if (pos_x < 0 || pos_x >= WIDTH)
		return ;
	if (pos_y < 0 || pos_y >= HEIGHT)
		return ;
	mlx_put_pixel(graphics->image, pos_x, pos_y, color_value);
}

int	reverse_byte_order(int color)
{
	unsigned int	reversed;

	reversed = 0;
	reversed |= (color & 0xFF) << 24;
	reversed |= (color & 0xFF00) << 8;
	reversed |= (color & 0xFF0000) >> 8;
	reversed |= (color & 0xFF000000) >> 24;
	return (reversed);
}

void	draw_wall(t_graphics *quanta_field, int x, int draw_start,
		double draw_end)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = select_txtr(quanta_field, quanta_field->raycast->hit_type);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / draw_end;
	x_o = calculate_euclidean_norm(texture, quanta_field);
	y_o = (x - (HEIGHT / 2) + (draw_end / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (x < draw_start)
	{
		place_pixel(quanta_field, quanta_field->raycast->beam_index, x,
			reverse_byte_order(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		x++;
	}
}

void	display_ray(t_graphics *graphics, int ray_index)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	graphics->raycast->ray_length *= cos(quantum_phase_shift(graphics->raycast->beam_angle
				- graphics->player->direction));
	wall_height = (MAP_BLOCK_LEN / graphics->raycast->ray_length) * ((WIDTH / 2)
			/ tan(graphics->player->fov / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	graphics->raycast->beam_index = ray_index;
	draw_wall(graphics, top_pixel, bottom_pixel, wall_height);
	fill_floor_and_ceiling(graphics, ray_index, top_pixel, bottom_pixel);
}
