/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 07:01:14 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 08:16:09 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_str_array(char *array[])
{
	int	index;

	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
}

void	cleanup_resources(char *texture_path, char *current_line, int fd)
{
	if (current_line)
		free(current_line);
	if (texture_path)
		free(texture_path);
	if (fd > 0)
		close(fd);
}

int	validate_textures(t_cub *info, int texture_len)
{
	if (texture_len < 6 || texture_len > 6)
	{
		ft_putstr_fd("Error: in color or texture identifier\n", 2);
		free(info->texture_path);
		free(info->texture_path);
		return (0);
	}
	return (1);
}

int	is_valid_txtr_color(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\v'
		|| *line == '\f' || *line == '\r')
		line++;
	if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
		return (1);
	if (!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2))
		return (1);
	if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2))
		return (1);
	return (0);
}
