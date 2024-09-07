/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:14:13 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:15:51 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**split_and_validate_path(char *path)
{
	char	**parts;

	parts = ft_split(path, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		if (parts)
			free_str_array(parts);
		return (NULL);
	}
	return (parts);
}

int	check_texture_type(char *type)
{
	return (ft_strncmp(type, "NO", 2) == 0 || ft_strncmp(type, "SO", 2) == 0
		|| ft_strncmp(type, "EA", 2) == 0 || ft_strncmp(type, "WE", 2) == 0);
}

int	validate_texture_path(char *path)
{
	if (!is_valid_png_path(path) || !file_exists(path))
		return (0);
	return (1);
}

int	initialize_texture(t_texture *texture, char **parts)
{
	texture->ident = ft_strdup(parts[0]);
	texture->path = ft_strdup(parts[1]);
	texture->next = NULL;
	return (texture->ident && texture->path);
}

t_texture	*create_texture(char *path)
{
	t_texture	*new_texture;
	char		**parts;

	new_texture = allocate_texture();
	if (!new_texture)
		return (NULL);
	parts = split_and_validate_path(path);
	if (!parts || (check_texture_type(parts[0])
			&& !validate_texture_path(parts[1])))
	{
		free(new_texture);
		if (parts)
			free_str_array(parts);
		return (NULL);
	}
	if (!initialize_texture(new_texture, parts))
	{
		free(new_texture);
		free_str_array(parts);
		return (NULL);
	}
	free_str_array(parts);
	return (new_texture);
}
