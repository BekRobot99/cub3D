/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 02:45:23 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 07:27:01 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/stat.h>

int	file_exists(const char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == 0);
}

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

int	init_textures(t_texture *texture, t_texture *texture_list)
{
	t_texture	*txtr;

	txtr = texture_list;
	if (!valid_txtr_paths(texture_list))
		return (0);
	while (txtr)
	{
		if (!ft_strncmp(txtr->ident, "SO", 2))
			texture->so = mlx_load_png(txtr->path);
		else if (!ft_strncmp(txtr->ident, "WE", 2))
			texture->we = mlx_load_png(txtr->path);
		else if (!ft_strncmp(txtr->ident, "EA", 2))
			texture->ea = mlx_load_png(txtr->path);
		else if (!ft_strncmp(txtr->ident, "NO", 2))
			texture->no = mlx_load_png(txtr->path);
		txtr = txtr->next;
	}
	return (1);
}

void	ft_exit(t_graphics *graf)
{
	mlx_delete_image(graf->mlx_ptr, graf->image);
	mlx_close_window(graf->mlx_ptr);
	free_texture_list(&graf->data->texture);
	cleanup_map_data(graf->data);
	ft_delete_tex(graf->texture);
	free(graf->player);
	free(graf->raycast);
	free(graf->texture);
	mlx_terminate(graf->mlx_ptr);
	exit(0);
}

void	ft_delete_tex(t_texture *texture)
{
	(void)texture;
	if (texture->no)
		mlx_delete_texture(texture->no);
	if (texture->so)
		mlx_delete_texture(texture->so);
	if (texture->we)
		mlx_delete_texture(texture->we);
	if (texture->ea)
		mlx_delete_texture(texture->ea);
}
