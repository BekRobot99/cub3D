/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:38:01 by abekri            #+#    #+#             */
/*   Updated: 2024/10/25 20:28:01 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// int	init_graphics(t_graphics *graf) // used directly in main
// {
// 	graf->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
// 	if (!graf->mlx_ptr)
// 	{
// 		ft_exit(graf);
// 		return (0);
// 	}
// 	return (1);
// }

void	handle_key_press(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_A)
		gfx->player->move_lt_rt = -1;
	else if (indent_info.key == MLX_KEY_D)
		gfx->player->move_lt_rt = 1;
	else if (indent_info.key == MLX_KEY_S)
		gfx->player->move_up_dwn = -1;
	else if (indent_info.key == MLX_KEY_W)
		gfx->player->move_up_dwn = 1;
	else if (indent_info.key == MLX_KEY_LEFT)
		gfx->player->dir_rotation = -1;
	else if (indent_info.key == MLX_KEY_RIGHT)
		gfx->player->dir_rotation = 1;
}

void	handle_key_release(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_D || indent_info.key == MLX_KEY_A)
		gfx->player->move_lt_rt = 0;
	else if (indent_info.key == MLX_KEY_S || indent_info.key == MLX_KEY_W)
		gfx->player->move_up_dwn = 0;
	else if (indent_info.key == MLX_KEY_LEFT
		|| indent_info.key == MLX_KEY_RIGHT)
		gfx->player->dir_rotation = 0;
}

void	handle_escape_key(mlx_key_data_t indent_info, t_graphics *gfx)
{
	if (indent_info.key == MLX_KEY_ESCAPE && (indent_info.action == MLX_PRESS
			|| indent_info.action == MLX_REPEAT))
	{
		ft_exit(gfx);
	}
}

// void	handle_key_event(mlx_key_data_t indent_info, void *graphics)
// {
// 	t_graphics	*gfx;

// 	gfx = (t_graphics *)graphics;
// 	handle_escape_key(indent_info, gfx);
// 	if (indent_info.action == MLX_PRESS)
// 		handle_key_press(indent_info, gfx);
// 	else if (indent_info.action == MLX_RELEASE)
// 		handle_key_release(indent_info, gfx);
// }

void	handle_key_event(mlx_key_data_t indent_info, void *graphics) //recoded
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
