/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:10:33 by abekri            #+#    #+#             */
/*   Updated: 2024/08/28 21:26:20 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2 || !is_valid_cub_ext(argv[1]))
	{
		ft_putstr_fd("Error: few arguments or invalid image extension\n", 2);
		exit(0);
	}
	return (0);
}
