/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 05:04:35 by abekri            #+#    #+#             */
/*   Updated: 2024/09/05 01:39:34 by abekri           ###   ########.fr       */
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
	grid_col = (next_pos_x / MAP_BLOCK_LEN);
	grid_row = (next_pos_y / MAP_BLOCK_LEN);
	if (graf->data->map_grid[grid_row][grid_col] != '1'
		&& (graf->data->square_map[grid_row][graf->player->pos_x
			/ MAP_BLOCK_LEN] != '1'
			&& graf->data->square_map[graf->player->pos_y
			/ MAP_BLOCK_LEN][grid_col] != '1'))
	{
		graf->player->pos_x = next_pos_x;
		graf->player->pos_y = next_pos_y;
	}
}

void	handle_player_movement(t_graphics *graf, double xoffset,
		double yoffset)
{
	if (graf->player->move_lt_rt == -1)
	{
		xoffset = MOVEMENT_SPEED * sin(graf->player->direction);
		yoffset = MOVEMENT_SPEED * (-cos(graf->player->direction));
	}
	if (graf->player->dir_rotation == 1)
		adjust_player_rotation(graf, 1);
	if (graf->player->dir_rotation == -1)
		adjust_player_rotation(graf, 0);
	if (graf->player->move_lt_rt == 1)
	{
		xoffset = MOVEMENT_SPEED * (-sin(graf->player->direction));
		yoffset = MOVEMENT_SPEED * cos(graf->player->direction);
	}
	if (graf->player->move_up_dwn == 1)
	{
		xoffset = MOVEMENT_SPEED * cos(graf->player->direction);
		yoffset = MOVEMENT_SPEED * sin(graf->player->direction);
	}
	if (graf->player->move_up_dwn == -1)
	{
		xoffset = -cos(graf->player->direction) * MOVEMENT_SPEED;
		yoffset = -sin(graf->player->direction) * MOVEMENT_SPEED;
	}
	update_player_position(graf, xoffset, yoffset);
}

void	draw_game(void *mlxl)
{
	t_graphics	*graf;

	graf = mlxl;
	mlx_delete_image(graf->mlx_ptr, graf->image);
	graf->image = mlx_new_image(graf->mlx_ptr, WIDTH, HEIGHT);
	handle_player_movement(graf, 0, 0); // the first position of the player;
	//(my partner part) a fucbtion that cast the rays which will use  (graf) as arguments;
}
