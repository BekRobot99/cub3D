/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 02:45:23 by abekri            #+#    #+#             */
/*   Updated: 2024/09/05 19:02:04 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <sys/stat.h>

int file_exists(const char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int valid_txtr_paths(t_texture *texture_list)
{
    t_texture *current_texture;

    current_texture = texture_list;
    while (current_texture)
    {
        if (!ft_strncmp(current_texture->ident, "SO", 2)
            || !ft_strncmp(current_texture->ident, "NO", 2)
            || !ft_strncmp(current_texture->ident, "EA", 2)
            || !ft_strncmp(current_texture->ident, "WE", 2))
        {
            printf("Debug: Skipping texture file: %s\n", current_texture->path);
        }
        current_texture = current_texture->next;
    }
    return (1);
}

int init_textures(t_texture *texture, t_texture *texture_list)
{
    texture = texture_list;
    if (!valid_txtr_paths(texture_list))
    {
        printf("Debug: Invalid texture paths\n");
        return (0);
    }
    while (texture)
    {
        if (!ft_strncmp(texture->ident, "SO", 2)
            || !ft_strncmp(texture->ident, "WE", 2)
            || !ft_strncmp(texture->ident, "EA", 2)
            || !ft_strncmp(texture->ident, "NO", 2))
        {
            printf("Debug: Skipping texture loading for %s\n", texture->ident);
        }
        texture = texture->next;
    }
    return (1);
}

void	ft_exit(t_graphics *graf)
{
	mlx_delete_image(graf->mlx_ptr, graf->image);
	mlx_close_window(graf->mlx_ptr);
	free_texture_list(&graf->data->texture);
	cleanup_map_data(graf->data);
	ft_delete_tex(graf->texture);
	free(graf->player);
	free(graf->raycast);
	free(graf->texture);
	mlx_terminate(graf->mlx_ptr);
	exit(0);
}

int init_game_loop(t_graphics *graf)
{
    char dir;

    printf("Debug: Starting init_game_loop\n");

    graf->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3D", false);
    if (!graf->mlx_ptr)
    {
        printf("Debug: Failed to create MLX window\n");
        return (ft_exit(graf), 0);
    }
    printf("Debug: MLX window created successfully\n");

    graf->image = mlx_new_image(graf->mlx_ptr, WIDTH, HEIGHT);
    if (!graf->image)
    {
        printf("Debug: Failed to create initial image\n");
        return (ft_exit(graf), 0);
    }

    if (!init_textures(graf->texture, graf->data->texture))
    {
        printf("Debug: Failed to initialize textures\n");
        return (ft_exit(graf), 0);
    }
    printf("Debug: Textures initialized successfully\n");

    dir = graf->data->map_grid[graf->data->ppos_y][graf->data->ppos_x];
    printf("Debug: Player direction: %c\n", dir);

    graf->player->pos_x = (graf->data->ppos_x * MAP_BLOCK_LEN) + MAP_BLOCK_LEN / 2;
    graf->player->pos_y = (graf->data->ppos_y * MAP_BLOCK_LEN) + MAP_BLOCK_LEN / 2;
    graf->player->fov = (FOV * M_PI / 180);

    if (dir == 'W')
        graf->player->direction = M_PI;
    else if (dir == 'N')
        graf->player->direction = 3 * M_PI / 2;
    else if (dir == 'E')
        graf->player->direction = 0;
    else if (dir == 'S')
        graf->player->direction = M_PI / 2;

    printf("Debug: Player position set to (%d, %d)\n", (int)graf->player->pos_x, (int)graf->player->pos_y);
    printf("Debug: Player direction set to %f\n", graf->player->direction);

	graf->image = mlx_new_image(graf->mlx_ptr, WIDTH, HEIGHT);
if (!graf->image)
{
    printf("Debug: Failed to create initial image\n");
    return (ft_exit(graf), 0);
}
    printf("Debug: Setting up MLX hooks\n");
    mlx_loop_hook(graf->mlx_ptr, &draw_game, graf);
    mlx_key_hook(graf->mlx_ptr, &handle_key_event, graf);

    printf("Debug: Starting MLX loop\n");
    mlx_loop(graf->mlx_ptr);

    printf("Debug: MLX loop ended\n");
    ft_exit(graf);
    return (1);
}

void ft_delete_tex(t_texture *texture)
{
	(void)texture; 
    // if (texture->no)
    //     mlx_delete_texture(texture->no);
    // if (texture->so)
    //     mlx_delete_texture(texture->so);
    // if (texture->we)
    //     mlx_delete_texture(texture->we);
    // if (texture->ea)
    //     mlx_delete_texture(texture->ea);
}
