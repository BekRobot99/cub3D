/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:30:22 by abekri            #+#    #+#             */
/*   Updated: 2024/10/25 19:13:01 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_line_content(char *current_line) //
{
	int i;

	i = 0;
	while (current_line[i])
	{
		if ((!ft_isdigit(current_line[i]) && current_line[i] != ',')
			|| (current_line[i] == ',' && current_line[i + 1]
				&& current_line[i + 1] == ','))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_color_format(char *current_line) //
{
	int flag;

	flag = 0;
	if (!check_and_update_flag(&current_line, &flag))
		return (0);
	if (!check_line_start_validity(current_line))
		return (0);
	if (!validate_line_content(current_line))
		return (0);
	return (1);
}

int	commas_qntt(char *colors) //
{
	int i;
	int qntt;

	i = 0;
	qntt = 0;
	while (colors[i])
		if (colors[i++] == ',')
			qntt++;
	return (qntt);
}

int	check_colors(char **texture_paths) //
{
	char *tmp;
	int index;

	index = 0;
	while (texture_paths[index])
	{
		tmp = texture_paths[index];
		while (*tmp == ' ' || *tmp == '\t' || *tmp == '\n' || *tmp == '\v'
			|| *tmp == '\f' || *tmp == '\r')
			tmp++;
		if (tmp[0] == 'F' || tmp[0] == 'C')
		{
			if (!is_valid_color_format(tmp) || commas_qntt(tmp) != 2)
			{
				ft_putstr_fd("Error : txtr or clr not found for map element\n",
					2);
				return (0);
			}
		}
		index++;
	}
	return (1);
}
