/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   photon_trajectory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:48:25 by amohame2          #+#    #+#             */
/*   Updated: 2024/09/05 19:02:35 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

#define TAU 6.28318530717958647692

 double	quantum_phase_shift(double phase)
{
	while (phase >= TAU)
		phase -= TAU;
	while (phase < 0)
		phase += TAU;
	return (phase);
}

 double	initial_wavefront_phase(t_gamer *observer, double field_span)
{
	return (quantum_phase_shift(observer->direction - (field_span / 2)));
}

void emit_photon_array(t_graphics *quanta_field)
{
    printf("Debug: Entering emit_photon_array\n");

    if (!quanta_field || !quanta_field->player)
    {
        printf("Debug: Null pointer detected in emit_photon_array\n");
        return;
    }

    double wavefront_phase;
    double phase_increment;
    int photon_count;

    wavefront_phase = initial_wavefront_phase(quanta_field->player, quanta_field->player->fov);
    phase_increment = quanta_field->player->fov / WIDTH;
    photon_count = 0;

    printf("Debug: Starting photon emission loop\n");
    while (photon_count < WIDTH)
    {
        printf("Debug: Emitting photon %d\n", photon_count);
        trace_photon_path(quanta_field, wavefront_phase, photon_count);
        wavefront_phase = quantum_phase_shift(wavefront_phase + phase_increment);
        photon_count++;
    }
    printf("Debug: Finished emitting photons\n");
}


void draw_wall(t_graphics *quanta_field, int x, int draw_start, int draw_end)
{
    printf("Debug: Entering draw_wall function\n");
    printf("Debug: x: %d, draw_start: %d, draw_end: %d\n", x, draw_start, draw_end);

    if (!quanta_field || !quanta_field->image || !quanta_field->data || !quanta_field->raycast)
    {
        printf("Debug: Null pointer detected in draw_wall\n");
        return;
    }

    int y;
    uint32_t color;

    // Draw ceiling
    printf("Debug: Drawing ceiling\n");
    for (y = 0; y < draw_start; y++)
    {
        if (y >= HEIGHT)
        {
            printf("Debug: Ceiling y out of bounds: %d\n", y);
            break;
        }
        mlx_put_pixel(quanta_field->image, x, y, quanta_field->data->ceiling_color);
    }

    // Draw wall
    printf("Debug: Drawing wall\n");
    for (y = draw_start; y < draw_end; y++)
    {
        if (y >= HEIGHT)
        {
            printf("Debug: Wall y out of bounds: %d\n", y);
            break;
        }
        if (quanta_field->raycast->hit_type == 0) // planar collision
        {
            if (!quanta_field->data->texture->no || !quanta_field->data->texture->no->pixels)
            {
                printf("Debug: Null texture pointer for planar collision\n");
                return;
            }
            color = quanta_field->data->texture->no->pixels[(y * quanta_field->data->texture->no->width + x) * 4];
        }
        else // axial collision
        {
            if (!quanta_field->data->texture->ea || !quanta_field->data->texture->ea->pixels)
            {
                printf("Debug: Null texture pointer for axial collision\n");
                return;
            }
            color = quanta_field->data->texture->ea->pixels[(y * quanta_field->data->texture->ea->width + x) * 4];
        }
        mlx_put_pixel(quanta_field->image, x, y, color);
    }

    // Draw floor
    printf("Debug: Drawing floor\n");
    for (y = draw_end; y < HEIGHT; y++)
    {
        mlx_put_pixel(quanta_field->image, x, y, quanta_field->data->floor_color);
    }

    printf("Debug: Exiting draw_wall function\n");
}
void trace_photon_path(t_graphics *quanta_field, double wavefront_phase, int photon_count)
{
    printf("Debug: Tracing photon path for photon %d\n", photon_count);

    if (!quanta_field || !quanta_field->raycast)
    {
        printf("Debug: Null pointer detected in trace_photon_path\n");
        return;
    }

    t_castray *quantum_state = quanta_field->raycast;
    double wall_height;
    int draw_start, draw_end;

    printf("Debug: Setting quantum_state parameters\n");
    quantum_state->beam_angle = wavefront_phase;
    quantum_state->beam_index = photon_count;

    printf("Debug: Calling analyze_planar_intersections\n");
    analyze_planar_intersections(quanta_field, quantum_state);
    printf("Debug: analyze_planar_intersections completed\n");

    printf("Debug: Calling analyze_axial_intersections\n");
    analyze_axial_intersections(quanta_field, quantum_state);
    printf("Debug: analyze_axial_intersections completed\n");

    printf("Debug: Calculating ray length\n");
    if (quantum_state->intrsxn_x_horz == -1 || (quantum_state->intrsxn_x_vert != -1 &&
        calculate_euclidean_norm(quanta_field->player->pos_x, quanta_field->player->pos_y,
        quantum_state->intrsxn_x_vert, quantum_state->intrsxn_y_vert) <
        calculate_euclidean_norm(quanta_field->player->pos_x, quanta_field->player->pos_y,
        quantum_state->intrsxn_x_horz, quantum_state->intrsxn_y_horz)))
    {
        quantum_state->ray_length = calculate_euclidean_norm(quanta_field->player->pos_x,
            quanta_field->player->pos_y, quantum_state->intrsxn_x_vert, quantum_state->intrsxn_y_vert);
        quantum_state->hit_type = 1; // axial collision
    }
    else
    {
        quantum_state->ray_length = calculate_euclidean_norm(quanta_field->player->pos_x,
            quanta_field->player->pos_y, quantum_state->intrsxn_x_horz, quantum_state->intrsxn_y_horz);
        quantum_state->hit_type = 0; // planar collision
    }
    printf("Debug: Ray length calculated: %f\n", quantum_state->ray_length);

    printf("Debug: Applying fisheye correction\n");
    quantum_state->ray_length *= cos(quanta_field->player->direction - wavefront_phase);

    printf("Debug: Calculating wall height\n");
    wall_height = (MAP_BLOCK_LEN / quantum_state->ray_length) * ((WIDTH / 2) / tan(FOV / 2));
    printf("Debug: Wall height calculated: %f\n", wall_height);

    printf("Debug: Calculating draw start and end points\n");
    draw_start = (HEIGHT / 2) - (wall_height / 2);
    draw_end = (HEIGHT / 2) + (wall_height / 2);

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= HEIGHT)
        draw_end = HEIGHT - 1;

    printf("Debug: Draw start: %d, Draw end: %d\n", draw_start, draw_end);

    printf("Debug: Calling draw_wall\n");
    draw_wall(quanta_field, photon_count, draw_start, draw_end);
    printf("Debug: draw_wall completed\n");

    printf("Debug: Finished tracing photon path for photon %d\n", photon_count);
}


 double	calculate_euclidean_norm(double x1, double y1, double x2,
		double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

 void   analyze_planar_intersections(t_graphics *quanta_field, t_castray *quantum_state)
{
    double  y_step, x_step;
    double  x_check, y_check;
    int     map_x, map_y;

    y_step = MAP_BLOCK_LEN;
    if (sin(quantum_state->beam_angle) > 0)
        y_check = (int)(quanta_field->player->pos_y / MAP_BLOCK_LEN) * MAP_BLOCK_LEN + MAP_BLOCK_LEN;
    else
    {
        y_check = (int)(quanta_field->player->pos_y / MAP_BLOCK_LEN) * MAP_BLOCK_LEN - 0.001;
        y_step *= -1;
    }

    x_step = MAP_BLOCK_LEN / tan(quantum_state->beam_angle);
    x_check = quanta_field->player->pos_x + (y_check - quanta_field->player->pos_y) / tan(quantum_state->beam_angle);

    while (1)
    {
        map_x = (int)(x_check / MAP_BLOCK_LEN);
        map_y = (int)(y_check / MAP_BLOCK_LEN);

        if (map_x < 0 || map_y < 0 || map_x >= quanta_field->data->nb_cols || map_y >= quanta_field->data->nb_lines)
        {
            quantum_state->intrsxn_x_horz = -1;
            quantum_state->intrsxn_y_horz = -1;
            return;
        }

        if (quanta_field->data->map_grid[map_y][map_x] == '1')
        {
            quantum_state->intrsxn_x_horz = x_check;
            quantum_state->intrsxn_y_horz = y_check;
            return;
        }

        x_check += x_step;
        y_check += y_step;
    }
}

void    analyze_axial_intersections(t_graphics *quanta_field, t_castray *quantum_state)
{
    double  x_step, y_step;
    double  x_check, y_check;
    int     map_x, map_y;

    x_step = MAP_BLOCK_LEN;
    if (cos(quantum_state->beam_angle) > 0)
        x_check = (int)(quanta_field->player->pos_x / MAP_BLOCK_LEN) * MAP_BLOCK_LEN + MAP_BLOCK_LEN;
    else
    {
        x_check = (int)(quanta_field->player->pos_x / MAP_BLOCK_LEN) * MAP_BLOCK_LEN - 0.001;
        x_step *= -1;
    }

    y_step = MAP_BLOCK_LEN * tan(quantum_state->beam_angle);
    y_check = quanta_field->player->pos_y + (x_check - quanta_field->player->pos_x) * tan(quantum_state->beam_angle);

    while (1)
    {
        map_x = (int)(x_check / MAP_BLOCK_LEN);
        map_y = (int)(y_check / MAP_BLOCK_LEN);

        if (map_x < 0 || map_y < 0 || map_x >= quanta_field->data->nb_cols || map_y >= quanta_field->data->nb_lines)
        {
            quantum_state->intrsxn_x_vert = -1;
            quantum_state->intrsxn_y_vert = -1;
            return;
        }

        if (quanta_field->data->map_grid[map_y][map_x] == '1')
        {
            quantum_state->intrsxn_x_vert = x_check;
            quantum_state->intrsxn_y_vert = y_check;
            return;
        }

        x_check += x_step;
        y_check += y_step;
    }
}