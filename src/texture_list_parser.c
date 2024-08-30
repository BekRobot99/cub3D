/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:42 by abekri            #+#    #+#             */
/*   Updated: 2024/08/30 23:12:05 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	skip_whitespace(char *current_line, int start_index)
{
	while (current_line[start_index] == ' '
		|| current_line[start_index] == '\t'
		|| current_line[start_index] == '\n'
		|| current_line[start_index] == '\v'
		|| current_line[start_index] == '\f'
		|| current_line[start_index] == '\r')
	{
		start_index++;
	}
	return (start_index);
}

t_texture	*allocate_texture(void)
{
	t_texture	*texture;

	texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	if (!texture)
		return (NULL);
	return (texture);
}

char	*skip_leading_whitespace(char *current_line)
{
	while (*current_line == ' ' || *current_line == '\t'
		|| *current_line == '\n' || *current_line == '\v'
		|| *current_line == '\f' || *current_line == '\r')
	{
		current_line++;
	}
	return (current_line);
}

void	extract_cardinal_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 2);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 2),
			ft_strlen(current_line));
}

void	extract_floor_ceiling_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 1);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 1),
			ft_strlen(current_line));
}

t_texture	*create_texture(char *current_line)
{
	t_texture	*texture;

	texture = allocate_texture();
	if (!texture)
		return (NULL);
	current_line = skip_leading_whitespace(current_line);
	if ((!ft_strncmp(current_line, "WE", 2) || !ft_strncmp(current_line, "EA",
				2)) || !ft_strncmp(current_line, "NO", 2)
		|| !ft_strncmp(current_line, "SO", 2))
	{
		extract_cardinal_texture(texture, current_line);
	}
	else if ((!ft_strncmp(current_line, "F", 1) || !ft_strncmp(current_line,
				"C", 1)))
	{
		extract_floor_ceiling_texture(texture, current_line);
	}
	texture->next = NULL;
	return (texture);
}

void	append_texture(t_texture **texture_list, t_texture *new_texture)
{
	t_texture	*current_texture;

	current_texture = *texture_list;
	if (*texture_list == NULL)
	{
		*texture_list = new_texture;
		return ;
	}
	while (current_texture->next)
		current_texture = current_texture->next;
	current_texture->next = new_texture;
}

int	build_texture_list(t_cub *info, t_texture **texture_list)
{
	int			path_index;
	t_texture	*new_texture;

	path_index = 0;
	while (info->texture_paths[path_index])
	{
		new_texture = create_texture(info->texture_paths[path_index++]);
		if (!new_texture)
			return (0);
		append_texture(texture_list, new_texture);
	}
	return (1);
}
