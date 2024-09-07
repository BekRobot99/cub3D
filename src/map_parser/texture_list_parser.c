/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:42 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:17:05 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <string.h>

t_texture	*allocate_texture(void)
{
	t_texture	*new_texture;

	new_texture = (t_texture *)malloc(sizeof(t_texture));
	if (!new_texture)
		return (NULL);
	return (new_texture);
}

void	extract_floor_ceiling_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 1);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 1),
			ft_strlen(current_line));
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
