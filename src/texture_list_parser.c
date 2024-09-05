/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_list_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohame2 <amohame2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:05:42 by abekri            #+#    #+#             */
/*   Updated: 2024/09/05 17:59:51 by amohame2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>


int is_valid_png_path(const char *path)
{
    const char *extension = strrchr(path, '.');
    return extension && strcmp(extension, ".png") == 0;
}

int	skip_whitespace(char *current_line, int start_index)
{
	while (current_line[start_index] == ' '
		|| current_line[start_index] == '\t'
		|| current_line[start_index] == '\n'
		|| current_line[start_index] == '\v'
		|| current_line[start_index] == '\f'
		|| current_line[start_index] == '\r')
	{
		start_index++;
	}
	return (start_index);
}

t_texture	*allocate_texture(void)
{
	t_texture	*texture;

	texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	if (!texture)
		return (NULL);
	return (texture);
}

char	*skip_leading_whitespace(char *current_line)
{
	while (*current_line == ' ' || *current_line == '\t'
		|| *current_line == '\n' || *current_line == '\v'
		|| *current_line == '\f' || *current_line == '\r')
	{
		current_line++;
	}
	return (current_line);
}

void	extract_cardinal_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 2);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 2),
			ft_strlen(current_line));
}

void	extract_floor_ceiling_texture(t_texture *texture, char *current_line)
{
	texture->ident = ft_substr(current_line, 0, 1);
	texture->path = ft_substr(current_line, skip_whitespace(current_line, 1),
			ft_strlen(current_line));
}

t_texture *create_texture(char *path)
{
    t_texture *new_texture;
    char **parts;

    printf("Debug: Creating texture for path: %s\n", path);

    new_texture = (t_texture *)malloc(sizeof(t_texture));
    if (!new_texture)
    {
        printf("Debug: Failed to allocate memory for new texture\n");
        return NULL;
    }

    parts = ft_split(path, ' ');
    if (!parts || !parts[0] || !parts[1])
    {
        printf("Debug: Invalid texture path format\n");
        free(new_texture);
        if (parts)
            free_str_array(parts);
        return NULL;
    }

    if ((ft_strncmp(parts[0], "NO", 2) == 0 || ft_strncmp(parts[0], "SO", 2) == 0 ||
         ft_strncmp(parts[0], "EA", 2) == 0 || ft_strncmp(parts[0], "WE", 2) == 0))
    {
        if (!is_valid_png_path(parts[1]) || !file_exists(parts[1]))
        {
            printf("Debug: Invalid or non-existent texture file for %s: %s\n", parts[0], parts[1]);
            free(new_texture);
            free_str_array(parts);
            return NULL;
        }
    }

    new_texture->ident = ft_strdup(parts[0]);
    new_texture->path = ft_strdup(parts[1]);
    new_texture->next = NULL;

    free_str_array(parts);

    printf("Debug: Texture created successfully\n");
    return new_texture;
}
void append_texture(t_texture **texture_list, t_texture *new_texture)
{
    t_texture *current;

    printf("Debug: Appending new texture to list\n");

    if (*texture_list == NULL)
    {
        *texture_list = new_texture;
    }
    else
    {
        current = *texture_list;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_texture;
    }

    printf("Debug: Texture appended successfully\n");
}

int build_texture_list(t_cub *info, t_texture **texture_list)
{
    int         path_index;
    t_texture   *new_texture;

    printf("Debug: Entering build_texture_list\n");

    path_index = 0;
    while (info->texture_paths[path_index])
    {
        printf("Debug: Processing texture path %d: %s\n", path_index, info->texture_paths[path_index]);
        new_texture = create_texture(info->texture_paths[path_index]);
        if (!new_texture)
        {
            printf("Debug: Failed to create texture for path: %s\n", info->texture_paths[path_index]);
            return (0);
        }
        append_texture(texture_list, new_texture);
        path_index++;
    }

    printf("Debug: Texture list built successfully\n");
    return (1);
}
