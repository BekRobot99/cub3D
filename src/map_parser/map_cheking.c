/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cheking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 04:09:41 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:16:18 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	verify_element_dup(t_cub *info)
{
	int	ptr;
	int	index;

	index = 0;
	while (info->texture_paths[index])
	{
		ptr = index + 1;
		while (info->texture_paths[ptr])
		{
			if (!ft_strncmp(info->texture_paths[index],
					info->texture_paths[ptr], 2))
			{
				ft_putstr_fd("Error : player found more than ones in the map\n",
					2);
				return (0);
			}
			ptr++;
		}
		index++;
	}
	return (1);
}

int	is_valid_texture_or_color(char *current_line)
{
	while (*current_line == ' ' || *current_line == '\t'
		|| *current_line == '\n' || *current_line == '\v'
		|| *current_line == '\f' || *current_line == '\r')
		current_line++;
	if ((ft_strncmp(current_line, "SO", 2) == 0 || ft_strncmp(current_line,
				"NO", 2) == 0 || ft_strncmp(current_line, "WE", 2) == 0
			|| ft_strncmp(current_line, "EA", 2) == 0)
		&& (current_line[2] == '\t' || current_line[2] == ' '
			|| current_line[2] == '\n' || current_line[2] == '\f'
			|| current_line[2] == '\r' || current_line[2] == '\v'))
		return (1);
	else if ((ft_strncmp(current_line, "C", 1) == 0 || ft_strncmp(current_line,
				"F", 1) == 0) && (current_line[1] == ' '
			|| current_line[1] == '\t' || current_line[1] == '\n'
			|| current_line[1] == '\v' || current_line[1] == '\f'
			|| current_line[1] == '\r'))
		return (1);
	return (0);
}

int	validate_txtr_clr_list(char **texture_path, int texture_len)
{
	int	index;

	index = 0;
	if (texture_len != 6)
		return (0);
	while (index < texture_len)
	{
		if (!is_valid_texture_or_color(texture_path[index]))
		{
			ft_putstr_fd("Error : texture or color not found for map element\n",
				2);
			return (0);
		}
		index++;
	}
	return (1);
}

char	*read_map_content(t_cub *info)
{
	info->raw_map_data = ft_strdup("");
	while (info->current_line)
	{
		if (info->current_line[0] == 10)
		{
			ft_putstr_fd("Error: finding an empty line\n", 2);
			return (cleanup_resources(info->raw_map_data, info->current_line,
					-1), NULL);
		}
		info->raw_map_data = ft_strjoin(info->raw_map_data, info->current_line);
		free(info->current_line);
		info->current_line = get_next_line(info->fd);
	}
	return (info->raw_map_data);
}

int	parse_map_data(t_cub *info, int count)
{
	info->raw_map_data = read_map_content(info);
	if (!info->raw_map_data)
		return (0);
	info->map_grid = ft_split(info->raw_map_data, '\n');
	if (!info->map_grid)
	{
		free(info->raw_map_data);
		return (0);
	}
	free(info->raw_map_data);
	if (!validate_txtr_clr_list(info->texture_paths, count)
		|| !verify_element_dup(info) || !check_colors(info->texture_paths)
		|| !valid_map_boundaries(info->map_grid)
		|| !validate_map_edges(info->map_grid))
	{
		free_str_array(info->map_grid);
		return (0);
	}
	return (1);
}
