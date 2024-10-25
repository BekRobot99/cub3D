/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:42 by abekri            #+#    #+#             */
/*   Updated: 2024/10/25 18:17:34 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <string.h>

t_texture	*allocate_texture(void)//
{
	t_texture	*new_texture;

	new_texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	if (!new_texture)
		return (NULL);
	new_texture->ident = NULL;
	new_texture->path = NULL;
	new_texture->next = NULL;
	return (new_texture);
}

char	*extract_floor_ceiling_texture(char *current_line, char *key)// 
{
	if (!key)
		return (NULL);
	if (ft_strlen(key) == 2)
		return (ft_substr(current_line, skip_whitespace(current_line, 2),
				ft_strlen(current_line)));
	else if (ft_strlen(key) == 1)
		return (ft_substr(current_line, skip_whitespace(current_line, 1),
				ft_strlen(current_line)));
	return (NULL);
}

void	append_texture(t_texture **texture_list, t_texture *new_texture)// rebuild
{
	t_texture	*current;

	current = *texture_list;
	if (*texture_list == NULL)
	{
		(*texture_list) = new_texture;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_texture;
}

int	build_texture_list(t_cub *info, t_texture **texture_list)// rebuild
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
