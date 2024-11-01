/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:35:49 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 19:15:54 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#define MOVEMENT_SPEED 5
#define RATE_ROT 0.1

void	adjust_player_rotation(t_graphics *graf, int angle_pos)
{
	if (angle_pos != 1)
	{
		graf->player->direction -= RATE_ROT;
		if (graf->player->direction < 0)
			graf->player->direction += 2 * M_PI;
	}
	else
	{
		graf->player->direction += RATE_ROT;
		if (graf->player->direction > 2 * M_PI)
			graf->player->direction -= 2 * M_PI;
	}
}

void	update_player_position(t_graphics *graf, double offset_x,
		double offset_y)
{
	int	next_pos_x;
	int	next_pos_y;
	int	grid_row;
	int	grid_col;

	next_pos_x = roundf(graf->player->pos_x + offset_x);
	next_pos_y = roundf(graf->player->pos_y + offset_y);
	grid_row = (next_pos_x / MAP_BLOCK_LEN);
	grid_col = (next_pos_y / MAP_BLOCK_LEN);
	if (graf->data->map_grid[grid_col][grid_row] != '1'
		&& (graf->data->square_map[grid_col][graf->player->pos_x
			/ MAP_BLOCK_LEN] != '1'
			&& graf->data->square_map[graf->player->pos_y
			/ MAP_BLOCK_LEN][grid_row] != '1'))
	{
		graf->player->pos_x = next_pos_x;
		graf->player->pos_y = next_pos_y;
	}
}

void	handle_key_press(mlx_key_data_t indent_info, t_graphics *gfx)
{
	handle_move_left_right(indent_info, gfx);
	handle_move_up_down(indent_info, gfx);
}
