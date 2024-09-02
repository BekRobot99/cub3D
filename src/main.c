/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:10:33 by abekri            #+#    #+#             */
/*   Updated: 2024/09/02 02:48:22 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


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
	t_cub		cub;
	int			texture_len;
	t_texture	*texture_list;
	t_graphics	graf;

	texture_len = 0;
	texture_list = NULL;
	if (argc != 2 || !is_valid_cub_ext(argv[1]))
	{
		ft_putstr_fd("Error: few arguments or invalid image extension\n", 2);
		exit(0);
	}
	if (!load_map_data(argv[1], &cub, &texture_len))
		return (0);
	if (!check_and_format_map(&cub))
		return (0);
	if (build_texture_list(&cub, &texture_list))
		return (cleanup_map_data(&cub), free_texture_list(&texture_list), 0);
	if (!process_texture_colors(&cub, texture_list))
		return (cleanup_map_data(&cub), free_texture_list(&texture_list), 0);
	find_player_position(&cub);
	calculate_map_dimensions(&cub);
	cub.texture = texture_list;
	if (!cub.texture || WIDTH > 2600 || HEIGHT > 1500 || FOV <= 0 || FOV >= 180)
		return (free_texture_list(&cub.texture), cleanup_map_data(&cub), 0);
	graf.player = (t_gamer *)ft_calloc(sizeof(t_gamer), 1);
	graf.raycast = (t_castray *)ft_calloc(sizeof(t_castray), 1);
	graf.texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	graf.data = &cub;
	init_game_loop(&graf);
}
