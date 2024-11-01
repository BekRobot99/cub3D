/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_checking1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 06:58:18 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:57:59 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_and_update_flag(char **current_line, int *flag)
{
	while (**current_line == ' ' || **current_line == '\t'
		|| **current_line == '\n' || **current_line == '\v'
		|| **current_line == '\f' || **current_line == '\r'
		|| **current_line == 'F' || **current_line == 'C')
	{
		if (**current_line == 'F' || **current_line == 'C')
			(*flag)++;
		(*current_line)++;
	}
	return (*flag == 1);
}

int	check_line_start_validity(char *current_line)
{
	return (ft_isdigit(current_line[(ft_strlen(current_line) - 1)])
		&& ft_isdigit(current_line[0]));
}

int	process_lines(t_cub *info, int *texture_count)
{
	info->texture_path = ft_strdup("");
	while (info->current_line && info->current_line[0] != '1'
		&& info->current_line[0] != 32)
	{
		if (is_valid_txtr_color(info->current_line))
		{
			info->texture_path = ft_strjoin(info->texture_path,
					info->current_line);
			(*texture_count)++;
		}
		free(info->current_line);
		info->current_line = get_next_line(info->fd);
	}
	return (1);
}

int	validate_textures_len(t_cub *info, int texture_len)
{
	if (texture_len < 6 || texture_len > 6)
	{
		ft_putstr_fd("Error: in color or texture identifier\n", 2);
		free(info->texture_path);
		free(info->current_line);
		return (0);
	}
	return (1);
}

int	validate_textures(t_cub *info, int texture_len)
{
	if (!validate_textures_len(info, texture_len))
	{
		cleanup_resources(NULL, NULL, info->fd);
		return (0);
	}
	return (1);
}
