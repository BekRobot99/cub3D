/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 06:59:24 by abekri            #+#    #+#             */
/*   Updated: 2024/10/25 17:21:03 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_horizontal_walls(char **raw_map_data)//
{
	int	row;
	int	col;

	row = 0;
	while (raw_map_data[row])
	{
		col = 0;
		while (raw_map_data[row][col])
		{
			if (raw_map_data[row][col] != '1' && raw_map_data[row][col] != ' ')
			{
				if (raw_map_data[row][col + 1] == ' ' || raw_map_data[row][col
					- 1] == ' ')
				{
					ft_putstr_fd("Error: in horizontal lines in the map\n", 2);
					return (0);
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	check_vertical_walls(char **raw_map_data)//
{
	int	col;
	int	row;

	row = 0;
	while (raw_map_data[row])
	{
		col = 0;
		while (raw_map_data[row][col])
		{
			if (raw_map_data[row][col] != ' ' && raw_map_data[row][col] != '1')
			{
				if (raw_map_data[row + 1][col] == ' ' || raw_map_data[row
					- 1][col] == ' ')
				{
					ft_putstr_fd("Error: errors in map in vertical lines\n", 2);
					return (0);
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

char	*pad_map_line(char *current_line, int max_line_size)//
{
	int		line_index;
	char	*new_line;

	line_index = 0;
	new_line = ft_calloc(sizeof(char), (max_line_size + 1));
	if (!new_line)
		return (NULL);
	while (current_line[line_index])
	{
		new_line[line_index] = current_line[line_index];
		line_index++;
	}
	while (max_line_size > line_index)
	{
		new_line[line_index] = ' ';
		line_index++;
	}
	new_line[line_index] = '\0';
	return (new_line);
}

int	count_map_lines(char **raw_map_data)//
{
	int	line_index;

	line_index = 0;
	while (raw_map_data[line_index])
		line_index++;
	return (line_index);
}
