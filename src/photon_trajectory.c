/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_trajectory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:25:25 by amohame2          #+#    #+#             */
/*   Updated: 2024/09/02 16:35:33 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TAU 6.28318530717958647692

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_trajectory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:00:00 by abekri            #+#    #+#             */
/*   Updated: 2024/09/02 15:00:00 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

#define TAU 6.28318530717958647692

static double	quantum_phase_shift(double phase)
{
	while (phase >= TAU)
		phase -= TAU;
	while (phase < 0)
		phase += TAU;
	return (phase);
}

static double	initial_wavefront_phase(t_gamer *observer, double field_span)
{
	return (quantum_phase_shift(observer->direction - (field_span / 2)));
}

void	emit_photon_array(t_graphics *quanta_field)
{
	double	wavefront_phase;
	double	phase_increment;
	int		photon_count;

	wavefront_phase = initial_wavefront_phase(quanta_field->player,
			quanta_field->player->fov);
	phase_increment = quanta_field->player->fov / WIDTH;
	photon_count = 0;
	while (photon_count < WIDTH)
	{
		trace_photon_path(quanta_field, wavefront_phase, photon_count);
		wavefront_phase = quantum_phase_shift(wavefront_phase
				+ phase_increment);
		photon_count++;
	}
}
static void	trace_photon_path(t_graphics *quanta_field, double wavefront_phase,
		int photon_count)
{
	t_castray	*quantum_state;

	quantum_state = quanta_field->raycast;
	quantum_state->beam_angle = wavefront_phase;
	quantum_state->beam_index = photon_count;
	analyze_planar_intersections(quanta_field, quantum_state);
	analyze_axial_intersections(quanta_field, quantum_state);
	if (quantum_state->intrsxn_x_horz == -1 || (quantum_state->intrsxn_x_vert !=
			-1 && calculate_euclidean_norm(quanta_field->player->pos_x,
				quanta_field->player->pos_y, quantum_state->intrsxn_x_vert,
				quantum_state->intrsxn_y_vert) < calculate_euclidean_norm(quanta_field->player->pos_x,
				quanta_field->player->pos_y, quantum_state->intrsxn_x_horz,
				quantum_state->intrsxn_y_horz)))
	{
		quantum_state->ray_length = calculate_euclidean_norm(quanta_field->player->pos_x,
				quanta_field->player->pos_y, quantum_state->intrsxn_x_vert,
				quantum_state->intrsxn_y_vert);
		quantum_state->hit_type = 1; // axial collision
	}
	else
	{
		quantum_state->ray_length = calculate_euclidean_norm(quanta_field->player->pos_x,
				quanta_field->player->pos_y, quantum_state->intrsxn_x_horz,
				quantum_state->intrsxn_y_horz);
		quantum_state->hit_type = 0; // planar collision
	}
}

static double	calculate_euclidean_norm(double x1, double y1, double x2,
		double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}