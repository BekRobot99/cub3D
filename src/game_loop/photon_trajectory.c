/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_trajectory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:48:25 by amohame2          #+#    #+#             */
/*   Updated: 2024/10/27 18:01:40 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

#define TAU 6.28318530717958647692

float	quantum_phase_shift(float phase)//order of operations is changed
{
	if (phase < 0)
		phase += (TAU);
	if (phase > (TAU))
		phase -= (TAU);
	return (phase);
}

void	increment_ray_angle(t_graphics *quanta_field)//
{
	quanta_field->raycast->beam_angle += (quanta_field->player->fov / WIDTH);
}

void	initial_wavefront_phase(t_graphics *quanta_field)//
{
	quanta_field->raycast->beam_angle = quanta_field->player->direction
		- (quanta_field->player->fov / 2);
}

void	emit_photon_array(t_graphics *quanta_field)//done 
{
	int		photon_count;
	double	wavefront_phase;

	photon_count = 0;
	initial_wavefront_phase(quanta_field);
	while (photon_count < WIDTH)
	{
		wavefront_phase = trace_photon_path(quanta_field);//
		display_ray(quanta_field, photon_count);//
		increment_ray_angle(quanta_field);//
		photon_count++;
	}
}
