/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:46:04 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:16:06 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	open_file(char *file_path, t_cub *info)
{
	info->fd = open(file_path, O_RDONLY);
	if (info->fd == -1)
		return (ft_putstr_fd("Error: fd is not valid\n", 2), 0);
	return (1);
}

int	read_first_line(t_cub *info)
{
	info->current_line = get_next_line(info->fd);
	if (info->current_line == NULL)
		return (ft_putstr_fd("Error: fd is empty\n", 2), 0);
	info->texture_path = ft_strdup("");
	return (1);
}

int	process_lines(t_cub *info, int *texture_count)
{
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

int	load_map_data(char *file_path, t_cub *info, int *texture_len)
{
	if (!open_file(file_path, info))
		return (0);
	if (!read_first_line(info))
		return (0);
	process_lines(info, texture_len);
	if (!validate_textures(info, *texture_len))
		return (cleanup_resources(NULL, NULL, info->fd), 0);
	info->texture_paths = ft_split(info->texture_path, '\n');
	if (!info->texture_paths)
		return (cleanup_resources(info->texture_path, NULL, info->fd), 0);
	if (!parse_map_data(info, *texture_len))
		return (cleanup_resources(info->texture_path, NULL, info->fd),
			free_str_array(info->texture_paths), 0);
	return (cleanup_resources(info->texture_path, info->current_line, info->fd),
		1);
}
