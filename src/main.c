/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:10:33 by abekri            #+#    #+#             */
/*   Updated: 2024/09/05 19:02:09 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"



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



int	main(int argc, char **argv)
{
    t_cub		cub;
    int			texture_len;
    t_texture	*texture_list;
    t_graphics	graf;

    printf("Debug: Starting main function\n");

    texture_len = 0;
    texture_list = NULL;

    if (argc != 2 || !is_valid_cub_ext(argv[1]))
    {
        ft_putstr_fd("Error: few arguments or invalid image extension\n", 2);
        exit(0);
    }

    printf("Debug: Arguments validated\n");

    if (!load_map_data(argv[1], &cub, &texture_len))
    {
        printf("Debug: Failed to load map data\n");
        return (0);
    }
    printf("Debug: Map data loaded successfully\n");

    if (!check_and_format_map(&cub))
    {
        printf("Debug: Failed to check and format map\n");
        return (0);
    }
    printf("Debug: Map checked and formatted successfully\n");
	


  printf("Debug: About to build texture list\n");
if (!build_texture_list(&cub, &texture_list))
{
    printf("Debug: Failed to build texture list\n");
    return (cleanup_map_data(&cub), free_texture_list(&texture_list), 0);
}
printf("Debug: Texture list built successfully\n");

    if (!process_texture_colors(&cub, texture_list))
    {
        printf("Debug: Failed to process texture colors\n");
        return (cleanup_map_data(&cub), free_texture_list(&texture_list), 0);
    }
    printf("Debug: Texture colors processed successfully\n");

    find_player_position(&cub);
    calculate_map_dimensions(&cub);
    cub.texture = texture_list;

    if (!cub.texture || WIDTH > 2600 || HEIGHT > 1500 || FOV <= 0 || FOV >= 180)
    {
        printf("Debug: Invalid texture or dimensions\n");
        return (free_texture_list(&cub.texture), cleanup_map_data(&cub), 0);
    }

    graf.player = (t_gamer *)ft_calloc(sizeof(t_gamer), 1);
    graf.raycast = (t_castray *)ft_calloc(sizeof(t_castray), 1);
    graf.texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
    graf.data = &cub;

    printf("Debug: Structures initialized\n");
    printf("Debug: Calling init_game_loop\n");

    if (!init_game_loop(&graf))
    {
        printf("Debug: init_game_loop failed\n");
        return (0);
    }

    printf("Debug: init_game_loop completed\n");
    return (0);
}
