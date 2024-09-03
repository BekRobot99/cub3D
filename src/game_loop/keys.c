/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:38:01 by abekri            #+#    #+#             */
/*   Updated: 2024/09/03 03:57:49 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_key_event(mlx_key_data_t indent_info, void *graphics)
{
	t_graphics	*gfx;

	gfx = graphics;

	if (indent_info.key == MLX_KEY_ESCAPE && (indent_info.action == MLX_PRESS
			|| indent_info.action == MLX_REPEAT))
	{
		ft_exit(gfx);
	}
	else if (indent_info.key == MLX_KEY_A && (indent_info.action == MLX_PRESS))
		gfx->player->move_lt_rt = -1;
	else if (indent_info.key == MLX_KEY_D && (indent_info.action == MLX_PRESS))
		gfx->player->move_lt_rt = 1;
	else if (indent_info.key == MLX_KEY_S && (indent_info.action == MLX_PRESS))
		gfx->player->move_up_dwn = -1;
	else if (indent_info.key == MLX_KEY_W && indent_info.action == MLX_PRESS)
		gfx->player->move_up_dwn = 1;
	else if (indent_info.key == MLX_KEY_LEFT && indent_info.action == MLX_PRESS)
		gfx->player->dir_rotation = -1;
	else if (indent_info.key == MLX_KEY_RIGHT
		&& indent_info.action == MLX_PRESS)
		gfx->player->dir_rotation = 1;
	else if (indent_info.key == MLX_KEY_D
		&& (indent_info.action == MLX_RELEASE))
		gfx->player->move_lt_rt = 0;
	else if (indent_info.key == MLX_KEY_A
		&& (indent_info.action == MLX_RELEASE))
		gfx->player->move_lt_rt = 0;
	else if (indent_info.key == MLX_KEY_S
		&& (indent_info.action == MLX_RELEASE))
		gfx->player->move_up_dwn = 0;
	else if (indent_info.key == MLX_KEY_W
		&& (indent_info.action == MLX_RELEASE))
		gfx->player->move_up_dwn = 0;
	else if (indent_info.key == MLX_KEY_LEFT
		&& indent_info.action == MLX_RELEASE)
		gfx->player->dir_rotation = 0;
	else if (indent_info.key == MLX_KEY_RIGHT
		&& indent_info.action == MLX_RELEASE)
		gfx->player->dir_rotation = 0;
}
