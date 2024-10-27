/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:38:01 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 19:15:28 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_move_left_right(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_A)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->move_lt_rt = -1;
		else
			gfx->player->move_lt_rt = 0;
	}
	else if (indent_info.key == MLX_KEY_D)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->move_lt_rt = 1;
		else
			gfx->player->move_lt_rt = 0;
	}
}

void	handle_move_up_down(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_S)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->move_up_dwn = -1;
		else
			gfx->player->move_up_dwn = 0;
	}
	else if (indent_info.key == MLX_KEY_W)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->move_up_dwn = 1;
		else
			gfx->player->move_up_dwn = 0;
	}
}

void	handle_key_release(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_LEFT)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->dir_rotation = -1;
		else
			gfx->player->dir_rotation = 0;
	}
	else if (indent_info.key == MLX_KEY_RIGHT)
	{
		if (indent_info.action == MLX_PRESS)
			gfx->player->dir_rotation = 1;
		else
			gfx->player->dir_rotation = 0;
	}
}

void	handle_escape_key(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_ESCAPE && (indent_info.action == MLX_PRESS
			|| indent_info.action == MLX_REPEAT))
	{
		ft_exit(gfx);
	}
}

void	handle_key_event(mlx_key_data_t indent_info, void *graphics)
{
	t_graphics	*gfx;

	gfx = graphics;
	handle_escape_key(indent_info, gfx);
	handle_key_press(indent_info, gfx);
	handle_key_release(indent_info, gfx);
}
