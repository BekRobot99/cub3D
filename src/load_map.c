/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 02:46:04 by abekri            #+#    #+#             */
/*   Updated: 2024/08/29 03:37:32 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cleanup_resources(char *texture_path, char *current_line, int fd)
{
    if (current_line)
		free(current_line);
	if (texture_path)
		free(texture_path);
	if (fd > 0)
		close(fd);
}

int	validate_textures(t_cub *info, int texture_len)
{
	if (texture_len < 6 || texture_len > 6)
	{
		ft_putstr_fd("Error: in color or texture identifier\n", 2);
		free(info->texture_path);
		free(info->texture_path);
		return (0);
	}
	return (1);
}

int	is_valid_txtr_color(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\v'
		|| *line == '\f' || *line == '\r')
		line++;
	if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
		return (1);
	if (!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2))
		return (1);
	return (0);
}

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
	return (cleanup_resources(info->texture_path, info->current_line, info->fd),
		1);
}
