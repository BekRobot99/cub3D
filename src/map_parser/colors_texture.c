/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 01:42:54 by abekri            #+#    #+#             */
/*   Updated: 2024/10/25 18:53:54 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_rgb_values(char **colors)//
{
	int	component_index;

	component_index = 0;
	while (colors[component_index])
	{
		if (ft_atoi(colors[component_index]) > 255
			|| ft_atoi(colors[component_index]) < 0)
			return (free_str_array(colors), 0);
		component_index++;
	}
	return (free_str_array(colors), 1);
}

void	apply_colors(t_texture *current_texture, t_cub *info)//
{
	if (!ft_strncmp(current_texture->ident, "C", 2))
	{
		info->ceiling_clr = ft_split(current_texture->path, ',');
		return ;
	}
	else if (!ft_strncmp(current_texture->ident, "F", 2))
	{
		info->floor_clr = ft_split(current_texture->path, ',');
		return ;
	}
}


int	process_texture_colors(t_cub *info, t_texture *texture_list)//
{
	t_texture	*current_texture;

	info->ceiling_clr = NULL;
	info->floor_clr = NULL;
	current_texture = texture_list;
	while (current_texture)
	{
		if (!ft_strncmp(current_texture->ident, "F", 1)
			|| !ft_strncmp(current_texture->ident, "C", 1))
		{
			if (!validate_rgb_values(ft_split(current_texture->path, ',')))
			{
				write(1, "Error\ninvalid RGBA color\n", 26);
				return (0);
			}
			apply_colors(current_texture, info);
		}
		current_texture = current_texture->next;
	}
	return (1);
}
