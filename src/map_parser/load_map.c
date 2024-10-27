/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:46:04 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:53:02 by abekri           ###   ########.fr       */
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
	{
		return (ft_putstr_fd("Error: fd is empty\n", 2), 0);
	}
	return (1);
}

int	convert_textures_to_2d(t_cub *info)
{
	info->texture_paths = ft_split(info->texture_path, '\n');
	if (!info->texture_paths)
	{
		cleanup_resources(info->texture_path, NULL, info->fd);
		return (0);
	}
	return (1);
}

int	finalize_map_reading(t_cub *info, int texture_len)
{
	if (!parse_map_data(info, texture_len))
	{
		cleanup_resources(info->texture_path, NULL, info->fd);
		free_str_array(info->texture_paths);
		return (0);
	}
	cleanup_resources(info->texture_path, info->current_line, info->fd);
	return (1);
}

int	load_map_data(char *file_path, t_cub *info, int *texture_len)
{
	if (!open_file(file_path, info))
		return (0);
	if (!read_first_line(info))
		return (0);
	if (!process_lines(info, texture_len))
		return (0);
	if (!validate_textures(info, *texture_len))
		return (0);
	if (!convert_textures_to_2d(info))
		return (0);
	if (!finalize_map_reading(info, *texture_len))
		return (0);
	return (1);
}
