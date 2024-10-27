/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:06:30 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 16:15:40 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	reverse_byte_order(int color)//
{
	unsigned int	reversed;

	reversed = 0;
	reversed |= (color & 0xFF) << 24;
	reversed |= (color & 0xFF00) << 8;
	reversed |= (color & 0xFF0000) >> 8;
	reversed |= (color & 0xFF000000) >> 24;
	return (reversed);
}

void	draw_wall(t_graphics *quanta_field, int x, int draw_start, double draw_end)// fixed
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
		place_pixel(quanta_field, quanta_field->raycast->beam_index, x, reverse_byte_order \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		x++;
	}
}

void	display_ray(t_graphics *graphics, int ray_index)// fixed
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	graphics->raycast->ray_length *= cos(quantum_phase_shift(graphics->raycast->beam_angle - graphics->player->direction));
	wall_height = (MAP_BLOCK_LEN / graphics->raycast->ray_length) * ((WIDTH / 2) / \
	tan(graphics->player->fov / 2));
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
