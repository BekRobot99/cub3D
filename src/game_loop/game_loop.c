/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 02:45:23 by abekri            #+#    #+#             */
/*   Updated: 2024/09/02 03:22:24 by abekri           ###   ########.fr       */
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

int	init_textures(t_texture *texture, t_texture *texture_list)
{
	t_texture	*texture;

	texture = texture_list;
	if (!valid_txtr_paths(texture_list))
		return (0);
	while (texture)
	{
		if (!ft_strncmp(texture->ident, "SO", 2))
			texture->so = mlx_load_png(texture->path);
		else if (!ft_strncmp(texture->ident, "WE", 2))
			texture->we = mlx_load_png(texture->path);
		else if (!ft_strncmp(texture->ident, "EA", 2))
			texture->ea = mlx_load_png(texture->path);
		else if (!ft_strncmp(texture->ident, "NO", 2))
			texture->no = mlx_load_png(texture->path);
		texture = texture->next;
	}
	return (1);
}

int	init_game_loop(t_graphics *graf)
{
	graf->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!graf->mlx_ptr)
		return (ft_exit(graf), 0);
	if (!init_textures(graf->texture, graf->data->texture))
		return (ft_exit(graf), 0);
	return (1);
}
