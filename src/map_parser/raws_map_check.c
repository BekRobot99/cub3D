/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raws_map_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:02:12 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:17:01 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_texture_list(t_texture **list_head)
{
	t_texture	*current_node;

	current_node = *list_head;
	while (current_node)
	{
		*list_head = current_node->next;
		free(current_node->ident);
		free(current_node->path);
		free(current_node);
		current_node = *list_head;
	}
	free(*list_head);
}

void	cleanup_map_data(t_cub *info)
{
	free_str_array(info->square_map);
	free_str_array(info->map_grid);
	free_str_array(info->texture_paths);
	if (info->floor_clr)
		free_str_array(info->floor_clr);
	if (info->ceiling_clr)
		free_str_array(info->ceiling_clr);
}

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
