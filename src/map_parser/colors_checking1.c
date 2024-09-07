/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_checking1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 06:58:18 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:15:44 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_and_update_flag(char **current_line, int *flag)
{
	while (**current_line == ' ' || **current_line == '\t'
		|| **current_line == '\n' || **current_line == '\v'
		|| **current_line == '\f' || **current_line == '\r'
		|| **current_line == 'F' || **current_line == 'C')
	{
		if (**current_line == 'F' || **current_line == 'C')
			(*flag)++;
		(*current_line)++;
	}
	return (*flag == 1);
}

int	check_line_start_validity(char *current_line)
{
	return (ft_isdigit(current_line[(ft_strlen(current_line) - 1)])
		&& ft_isdigit(current_line[0]));
}
