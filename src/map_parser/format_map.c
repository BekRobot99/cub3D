/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:47:12 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:50:10 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_max_line_length(char **raw_map_data)
{
	int	max_line_size;
	int	line_index;

	line_index = 0;
	max_line_size = ft_strlen(raw_map_data[0]);
	while (raw_map_data[line_index])
	{
		if ((int)ft_strlen(raw_map_data[line_index]) > max_line_size)
			max_line_size = ft_strlen(raw_map_data[line_index]);
		line_index++;
	}
	return (max_line_size);
}

int	initialize_square_map(t_cub *info, int max_line_size)
{
	int	line_idx;

	line_idx = 0;
	info->square_map = ft_calloc(sizeof(char *),
			(count_map_lines(info->map_grid) + 1));
	if (!info->square_map)
		return (0);
	while (info->map_grid[line_idx])
	{
		if (max_line_size == (int)ft_strlen(info->map_grid[line_idx]))
			info->square_map[line_idx] = ft_strdup(info->map_grid[line_idx]);
		else
			info->square_map[line_idx] = pad_map_line(info->map_grid[line_idx],
					max_line_size);
		line_idx++;
	}
	info->square_map[line_idx] = NULL;
	return (1);
}

int	validate_square_map(t_cub *info)
{
	info->map_height = count_map_lines(info->square_map);
	info->map_width = ft_strlen(info->square_map[0]);
	if (!check_vertical_walls(info->square_map)
		|| !check_horizontal_walls(info->square_map))
		return (free_str_array(info->square_map),
			free_str_array(info->map_grid), free_str_array(info->texture_paths),
			0);
	return (1);
}

int	check_and_format_map(t_cub *info)
{
	int	max_line_size;

	max_line_size = find_max_line_length(info->map_grid);
	if (!initialize_square_map(info, max_line_size))
		return (0);
	if (!validate_square_map(info))
		return (0);
	return (1);
}
