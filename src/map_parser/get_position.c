/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:18:56 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:16:02 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	is_valid_cub_ext(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!filename || !extension)
		return (0);
	else if (extension)
	{
		if (!ft_strcmp(extension, ".cub"))
			return (1);
	}
	return (0);
}

void	find_player_position(t_cub *info)
{
	int	col_idx;
	int	row_idx;

	row_idx = -1;
	while (info->square_map[++row_idx])
	{
		col_idx = -1;
		while (info->square_map[row_idx][++col_idx])
		{
			if (info->square_map[row_idx][col_idx] == 'W'
				|| info->square_map[row_idx][col_idx] == 'E'
				|| info->square_map[row_idx][col_idx] == 'N'
				|| info->square_map[row_idx][col_idx] == 'S')
			{
				info->ppos_x = col_idx;
				info->ppos_y = row_idx;
				return ;
			}
		}
	}
}

void	calculate_map_dimensions(t_cub *info)
{
	int	row_idx;
	int	col_idx;

	row_idx = 0;
	while (info->map_grid[row_idx])
	{
		col_idx = 0;
		while (info->map_grid[row_idx][col_idx])
			col_idx++;
		if (info->nb_cols < col_idx)
			info->nb_cols = col_idx;
		row_idx++;
	}
	info->nb_lines = row_idx;
}
