/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_trajectory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:48:25 by amohame2          #+#    #+#             */
/*   Updated: 2024/09/07 05:28:06 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

#define TAU 6.28318530717958647692

double	quantum_phase_shift(double phase)
{
	if (phase > (TAU))
		phase -= (TAU);
	if (phase < 0)
		phase += (TAU);
	return (phase);
}

void	increment_ray_angle(t_graphics *quanta_field)
{
	quanta_field->raycast->beam_angle += (quanta_field->player->fov / WIDTH);
}

void	initial_wavefront_phase(t_graphics *quanta_field)
{
	quanta_field->raycast->beam_angle = quanta_field->player->direction
		- (quanta_field->player->fov / 2);
}

void	emit_photon_array(t_graphics *quanta_field)
{
	int		photon_count;
	double	wavefront_phase;

	photon_count = 0;
	initial_wavefront_phase(quanta_field);
	while (photon_count < WIDTH)
	{
		wavefront_phase = trace_photon_path(quanta_field);
		display_ray(quanta_field, photon_count);
		increment_ray_angle(quanta_field);
		photon_count++;
	}
}

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

t_steps	calculate_planar_step_size(float angle)
{
	t_steps	steps;

	steps.y_step = MAP_BLOCK_LEN;
	steps.x_step = MAP_BLOCK_LEN / tan(angle);
	if ((in_quadrant(angle, 'y') && steps.x_step > 0) || (!in_quadrant(angle,
				'y') && steps.x_step < 0))
		steps.x_step *= -1;
	return (steps);
}

double	calculate_initial_intersection_y(t_graphics *gfx)
{
	return (floor(gfx->player->pos_y / MAP_BLOCK_LEN) * MAP_BLOCK_LEN);
}

double	calculate_initial_intersection_x(t_graphics *gfx, double y_check,
		float angle)
{
	return (gfx->player->pos_x + (y_check - gfx->player->pos_y) / tan(angle));
}

void	trace_planar_ray(double *x_check, double *y_check, t_steps steps,
		t_graphics *gfx)
{
	while (is_wall(*x_check, *y_check, gfx))
	{
		*x_check += steps.x_step;
		*y_check += steps.y_step;
	}
}

float	analyze_planar_intersections(t_graphics *gfx, float angle)
{
	double	x_check;
	double	y_check;
	t_steps	steps;
	int		draw_start;

	y_check = calculate_initial_intersection_y(gfx);
	steps = calculate_planar_step_size(angle);
	draw_start = adjust_intersection(angle, &y_check, &steps.y_step, 1);
	y_check -= draw_start;
	x_check = calculate_initial_intersection_x(gfx, y_check, angle);
	trace_planar_ray(&x_check, &y_check, steps, gfx);
	gfx->raycast->intrsxn_x_horz = x_check;
	gfx->raycast->intrsxn_y_horz = y_check;
	return (sqrt(pow(x_check - gfx->player->pos_x, 2) + pow(y_check
				- gfx->player->pos_y, 2)));
}

t_steps	calculate_step_size(float angle)
{
	t_steps	steps;

	steps.x_step = MAP_BLOCK_LEN;
	steps.y_step = MAP_BLOCK_LEN * tan(angle);
	if ((in_quadrant(angle, 'x') && steps.y_step < 0) || (!in_quadrant(angle,
				'x') && steps.y_step > 0))
		steps.y_step *= -1;
	return (steps);
}

double	calculate_initial_intersection_x1(t_graphics *gfx)
{
	return (floor(gfx->player->pos_x / MAP_BLOCK_LEN) * MAP_BLOCK_LEN);
}

double	calculate_initial_intersection_y1(t_graphics *gfx, double x_check,
		float angle)
{
	return (gfx->player->pos_y + (x_check - gfx->player->pos_x) * tan(angle));
}

void	trace_ray(double *x_check, double *y_check, t_steps steps,
		t_graphics *gfx)
{
	while (is_wall(*x_check, *y_check, gfx))
	{
		*x_check += steps.x_step;
		*y_check += steps.y_step;
	}
}

float	analyze_axial_intersections(t_graphics *gfx, float angle)
{
	double	x_check;
	double	y_check;
	t_steps	steps;
	int		draw_start;

	x_check = calculate_initial_intersection_x1(gfx);
	steps = calculate_step_size(angle);
	draw_start = adjust_intersection(angle, &x_check, &steps.x_step, 0);
	x_check -= draw_start;
	y_check = calculate_initial_intersection_y1(gfx, x_check, angle);
	trace_ray(&x_check, &y_check, steps, gfx);
	gfx->raycast->intrsxn_x_vert = x_check;
	gfx->raycast->intrsxn_y_vert = y_check;
	return (sqrt(pow(x_check - gfx->player->pos_x, 2) + pow(y_check
				- gfx->player->pos_y, 2)));
}
