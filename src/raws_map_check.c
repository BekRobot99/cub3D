/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raws_map_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:02:12 by abekri            #+#    #+#             */
/*   Updated: 2024/08/30 15:30:42 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*fetch_final_map_line(char **raw_map_data)
{
	int	index;

	index = 0;
	while (raw_map_data[index])
		index++;
	return (raw_map_data[index - 1]);
}

int	is_line_bordered_by_one(char *current_line)
{
	int	index;

	index = 0;
	while (current_line[index])
	{
		if (current_line[index] != ' ' && current_line[index] != '1')
			return (0);
		index++;
	}
	return (1);
}

int	validate_map_edges(char **raw_map_data)
{
	if (!raw_map_data[0])
	{
		ft_putstr_fd("Error : no map is found\n", 2);
		return (0);
	}
	if (!is_line_bordered_by_one(fetch_final_map_line(raw_map_data))
		|| !is_line_bordered_by_one(raw_map_data[0]))
	{
		ft_putstr_fd("Error : the map needs borders in first and last row\n",
			2);
		return (0);
	}
	return (1);
}
