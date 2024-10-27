/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:48:30 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:16:02 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

// float	analyze_axial_intersections(t_graphics *gfx, float angle)
// {
// 	double	x_check;
// 	double	y_check;
// 	t_steps	steps;
// 	int		draw_start;

// 	x_check = calculate_initial_intersection_x1(gfx);
// 	steps = calculate_step_size(angle);
// 	draw_start = adjust_intersection(angle, &x_check, &steps.x_step, 0);
// 	x_check -= draw_start;
// 	y_check = calculate_initial_intersection_y1(gfx, x_check, angle);
// 	trace_ray(&x_check, &y_check, steps, gfx);
// 	gfx->raycast->intrsxn_x_vert = x_check;
// 	gfx->raycast->intrsxn_y_vert = y_check;
// 	return (sqrt(pow(x_check - gfx->player->pos_x, 2) + pow(y_check
// 				- gfx->player->pos_y, 2)));
// }

float	analyze_axial_intersections(t_graphics *gfx, float angl)//recoded
{
	double	x_check;
	double	y_check;
	t_steps	steps;
	int		draw_start;

	steps.x_step = MAP_BLOCK_LEN;
	steps.y_step = MAP_BLOCK_LEN * tan(angl);
	x_check = floor(gfx->player->pos_x / MAP_BLOCK_LEN) * MAP_BLOCK_LEN;
	draw_start = adjust_intersection(angl, &x_check, &(steps.x_step), 0);
	y_check = gfx->player->pos_y + (x_check - gfx->player->pos_x) * tan(angl);
	if ((in_quadrant(angl, 'x') && steps.y_step < 0) || (!in_quadrant(angl, 'x')
			&& steps.y_step > 0))
		steps.y_step *= -1;
	while (is_wall(x_check - draw_start, y_check, gfx))
	{
		x_check += steps.x_step;
		y_check += steps.y_step;
	}
	gfx->raycast->intrsxn_x_vert = x_check;
	gfx->raycast->intrsxn_y_vert = y_check;
	return (sqrt(pow(x_check - gfx->player->pos_x, 2) + pow(y_check - gfx->player->pos_y,
				2)));
}
