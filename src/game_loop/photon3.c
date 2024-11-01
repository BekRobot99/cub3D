/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:52:18 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:42:53 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	trace_photon_path(t_graphics *quanta_field)
{
	double	wavefront_phase;
	double	phase_increment;

	quanta_field->raycast->hit_type = 0;
	wavefront_phase = analyze_planar_intersections(quanta_field,
			quantum_phase_shift(quanta_field->raycast->beam_angle));
	phase_increment = analyze_axial_intersections(quanta_field,
			quantum_phase_shift(quanta_field->raycast->beam_angle));
	if (phase_increment <= wavefront_phase)
		quanta_field->raycast->ray_length = phase_increment;
	else
	{
		quanta_field->raycast->ray_length = wavefront_phase;
		quanta_field->raycast->hit_type = 1;
	}
	return (quanta_field->raycast->ray_length);
}

int	is_wall(float pos_x, float pos_y, t_graphics *gfx)
{
	int	grid_x;
	int	grid_y;

	if (pos_x < 0 || pos_y < 0)
		return (0);
	grid_x = floor(pos_x / MAP_BLOCK_LEN);
	grid_y = floor(pos_y / MAP_BLOCK_LEN);
	if ((grid_y >= gfx->data->map_height || grid_x >= gfx->data->map_width))
		return (0);
	if (gfx->data->map_grid[grid_y]
		&& grid_x <= (int)ft_strlen(gfx->data->map_grid[grid_y]))
		if (gfx->data->map_grid[grid_y][grid_x] == '1')
			return (0);
	return (1);
}

int	in_quadrant(float radians, char axis)
{
	if (axis == 'x')
	{
		if (radians > 0 && radians < M_PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (radians > (M_PI / 2) && radians < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	adjust_intersection(double radius, double *pos, double *delta,
		int is_horizontal)
{
	if (is_horizontal)
	{
		if (radius > 0 && radius < M_PI)
		{
			*pos += MAP_BLOCK_LEN;
			return (-1);
		}
		*delta *= -1;
	}
	else
	{
		if (!(radius > M_PI / 2 && radius < 3 * M_PI / 2))
		{
			*pos += MAP_BLOCK_LEN;
			return (-1);
		}
		*delta *= -1;
	}
	return (1);
}
