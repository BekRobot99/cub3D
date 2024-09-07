/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:44:11 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:08:19 by abekri           ###   ########.fr       */
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

	floor_color = (ft_atoi(gfx->data->floor_clr[0]) << 24)
		| (ft_atoi(gfx->data->floor_clr[1]) << 16)
		| (ft_atoi(gfx->data->floor_clr[2]) << 8)
		| 255;
	ceiling_color = (ft_atoi(gfx->data->ceiling_clr[0]) << 24)
		| (ft_atoi(gfx->data->ceiling_clr[1]) << 16)
		| (ft_atoi(gfx->data->ceiling_clr[2]) << 8)
		| 255;
	current_pixel = bottom_pixel;
	while (current_pixel < HEIGHT)
	{
		place_pixel(gfx, ray_index, current_pixel++, floor_color);
	}
	current_pixel = 0;
	while (current_pixel < top_pixel)
	{
		place_pixel(gfx, ray_index, current_pixel++, ceiling_color);
	}
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
{
	if (pos_x < 0 || pos_x >= WIDTH)
		return ;
	if (pos_y < 0 || pos_y >= HEIGHT)
		return ;
	mlx_put_pixel(graphics->image, pos_x, pos_y, color_value);
}
