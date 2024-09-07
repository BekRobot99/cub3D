/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:03:42 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:17:08 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_png_path(const char *path)
{
	const char	*extension = strrchr(path, '.');

	return (extension && strcmp(extension, ".png") == 0);
}

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
