/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:25:44 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 07:31:34 by abekri           ###   ########.fr       */
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

void	set_player_direction(t_graphics *graf, char dir)
{
	if (dir == 'W')
		graf->player->direction = M_PI;
	else if (dir == 'N')
		graf->player->direction = 3 * M_PI / 2;
	else if (dir == 'E')
		graf->player->direction = 0;
	else if (dir == 'S')
		graf->player->direction = M_PI / 2;
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
	char	dir;

	if (!init_graphics(graf))
		return (0);
	if (!init_game_textures(graf))
		return (0);
	dir = graf->data->map_grid[graf->data->ppos_y][graf->data->ppos_x];
	set_player_direction(graf, dir);
	set_player_position_and_fov(graf);
	start_game_loop(graf);
	ft_exit(graf);
	return (1);
}
