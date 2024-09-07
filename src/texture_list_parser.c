/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:42 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 07:04:13 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>

void	extract_floor_ceiling_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 1);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 1),
			ft_strlen(current_line));
}

t_texture	*create_texture(char *path)
{
	t_texture	*new_texture;
	char		**parts;

	new_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!new_texture)
	{
		return (NULL);
	}
	parts = ft_split(path, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		free(new_texture);
		if (parts)
			free_str_array(parts);
		return (NULL);
	}
	if ((ft_strncmp(parts[0], "NO", 2) == 0 || ft_strncmp(parts[0], "SO",
				2) == 0 || ft_strncmp(parts[0], "EA", 2) == 0
			|| ft_strncmp(parts[0], "WE", 2) == 0))
	{
		if (!is_valid_png_path(parts[1]) || !file_exists(parts[1]))
		{
			free(new_texture);
			free_str_array(parts);
			return (NULL);
		}
	}
	new_texture->ident = ft_strdup(parts[0]);
	new_texture->path = ft_strdup(parts[1]);
	new_texture->next = NULL;
	free_str_array(parts);
	return (new_texture);
}

void	append_texture(t_texture **texture_list, t_texture *new_texture)
{
	t_texture	*current;

	if (*texture_list == NULL)
	{
		*texture_list = new_texture;
	}
	else
	{
		current = *texture_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_texture;
	}
}

int	build_texture_list(t_cub *info, t_texture **texture_list)
{
	int			path_index;
	t_texture	*new_texture;

	path_index = 0;
	while (info->texture_paths[path_index])
	{
		new_texture = create_texture(info->texture_paths[path_index]);
		if (!new_texture)
			return (0);
		append_texture(texture_list, new_texture);
		path_index++;
	}
	return (1);
}
