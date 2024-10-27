/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:25:44 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:37:51 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_game_textures(t_graphics *graf)
{
	if (!init_textures(graf->texture, graf->data->texture))
	{
		ft_exit(graf);
		return (0);
	}
	return (1);
}

void	set_player_direction(t_graphics *graf)
{
	char	dir;

	dir = graf->data->map_grid[graf->data->ppos_y][graf->data->ppos_x];
	if (dir == 'N')
		graf->player->direction = 3 * M_PI / 2;
	if (dir == 'S')
		graf->player->direction = M_PI / 2;
	if (dir == 'E')
		graf->player->direction = 0;
	if (dir == 'W')
		graf->player->direction = M_PI;
	graf->player->pos_x = (graf->data->ppos_x * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->pos_y = (graf->data->ppos_y * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->fov = (FOV * M_PI / 180);
}

void	set_player_position_and_fov(t_graphics *graf)
{
	graf->player->pos_x = (graf->data->ppos_x * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->pos_y = (graf->data->ppos_y * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->fov = (FOV * M_PI / 180);
}

void	start_game_loop(t_graphics *graf)
{
	mlx_key_hook(graf->mlx_ptr, &handle_key_event, graf);
	mlx_loop_hook(graf->mlx_ptr, &draw_game, graf);
	mlx_loop(graf->mlx_ptr);
}

int	init_game_loop(t_graphics *graf)
{
	graf->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!graf->mlx_ptr)
		return (ft_exit(graf), 0);
	if (!init_textures(graf->texture, graf->data->texture))
		return (ft_exit(graf), 0);
	set_player_direction(graf);
	start_game_loop(graf);
	ft_exit(graf);
	return (0);
}
