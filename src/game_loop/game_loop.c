/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 02:45:23 by abekri            #+#    #+#             */
/*   Updated: 2024/09/03 04:12:00 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_txtr_paths(t_texture *texture_list)
{
	t_texture		*current_texture;
	mlx_texture_t	*loaded_texture;

	current_texture = texture_list;
	while (current_texture)
	{
		if (!ft_strncmp(current_texture->ident, "SO", 2)
			|| !ft_strncmp(current_texture->ident, "NO", 2)
			|| !ft_strncmp(current_texture->ident, "EA", 2)
			|| !ft_strncmp(current_texture->ident, "WE", 2))
		{
			loaded_texture = mlx_load_png(current_texture->path);
			if (loaded_texture == NULL)
				return (0);
			mlx_delete_texture(loaded_texture);
		}
		current_texture = current_texture->next;
	}
	return (1);
}

void	ft_exit(t_graphics *graf)
{
	mlx_delete_image(graf->mlx_ptr, graf->image);
	mlx_close_window(graf->mlx_ptr);
	free_texture_list(graf->data->texture);
	cleanup_map_data(graf->data);
	ft_delete_tex(graf->texture);
	free(graf->player);
	free(graf->raycast);
	free(graf->texture);
	mlx_terminate(graf->mlx_ptr);
	exit(0);
}

int	init_game_loop(t_graphics *graf)
{
	char	dir;

	graf->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!graf->mlx_ptr)
		return (ft_exit(graf), 0);
	if (!init_textures(graf->texture, graf->data->texture))
		return (ft_exit(graf), 0);
	dir = graf->data->map_grid[graf->data->ppos_y][graf->data->ppos_x];
	if (dir == 'W')
		graf->player->direction = M_PI;
	if (dir == 'N')
		graf->player->direction = 3 * M_PI / 2;
	if (dir == 'E')
		graf->player->direction = 0;
	if (dir == 'S')
		graf->player->direction = M_PI / 2;
	graf->player->pos_x = (graf->data->ppos_x * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->pos_y = (graf->data->ppos_y * MAP_BLOCK_LEN) + MAP_BLOCK_LEN
		/ 2;
	graf->player->fov = (FOV * M_PI / 180);
	mlx_key_hook(graf->mlx_ptr, &handle_key_event, graf);
	mlx_loop(graf->mlx_ptr);
	ft_exit(graf);
	return (1);
}
