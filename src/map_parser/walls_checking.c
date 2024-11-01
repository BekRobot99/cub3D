/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:28:30 by abekri            #+#    #+#             */
/*   Updated: 2024/10/27 18:56:57 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_map_line(char *current_line, int *char_count)
{
	int	index;

	index = 0;
	while (current_line[index])
	{
		if ((current_line[index] != ' ' && current_line[index] != '0'
				&& current_line[index] != '1' && current_line[index] != '\n')
			&& !(current_line[index] == 'N' || current_line[index] == 'S'
				|| current_line[index] == 'W' || current_line[index] == 'E'))
			return (0);
		else if (current_line[index] == 'N' || current_line[index] == 'S'
			|| current_line[index] == 'W' || current_line[index] == 'E')
			(*char_count)++;
		index++;
	}
	return (1);
}

int	is_boundered_by_walls(char *current_line)
{
	size_t	len;

	while (*current_line == ' ' || *current_line == '\t'
		|| *current_line == '\n' || *current_line == '\v'
		|| *current_line == '\f' || *current_line == '\r')
		current_line++;
	len = ft_strlen(current_line);
	if (len == 0 || *current_line != '1' || current_line[len - 1] != '1')
		return (0);
	return (1);
}

int	valid_map_boundaries(char **raw_map_data)
{
	int	line_index;
	int	feature_count;

	feature_count = 0;
	line_index = 0;
	while (raw_map_data[line_index])
	{
		if (feature_count > 1
			|| !is_boundered_by_walls(raw_map_data[line_index])
			|| !validate_map_line(raw_map_data[line_index], &feature_count))
		{
			ft_putstr_fd("Error: errors in map\n", 2);
			return (0);
		}
		line_index++;
	}
	if (feature_count == 0)
	{
		ft_putstr_fd("Error: need more chars in map\n", 2);
		return (0);
	}
	return (1);
}
