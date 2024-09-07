/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:48:47 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 07:51:09 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
