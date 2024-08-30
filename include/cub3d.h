/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:07 by abekri            #+#    #+#             */
/*   Updated: 2024/08/30 18:40:43 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_cub
{
	int		fd;
	int		index;
	char	**map_grid;
	int		ppos_x;
	int		ppos_y;
	int		map_width;
	int		map_height;
	int		nb_lines;
	int		nb_cols;
	char	**texture_paths;
	char	**square_map;
	char	*texture_path;
	char	*raw_map_data;
	char	**rgb;
	char	**floor_clr;
	char	**ceiling_clr;
	char	*current_line;
}			t_cub;

char		*get_next_line(int fd);

void		free_str_array(char *array[]);
void		cleanup_resources(char *texture_path, char *current_line, int fd);
int			validate_textures(t_cub *info, int texture_len);
int			is_valid_txtr_color(char *line);
int			open_file(char *file_path, t_cub *info);
int			read_first_line(t_cub *info);
int			process_lines(t_cub *info, int *texture_count);
int			load_map_data(char *file_path, t_cub *info, int *texture_len);

int			is_valid_cub_ext(char *filename);

int			parse_map_data(t_cub *info, int count);
char		*read_map_content(t_cub *info);
int			validate_txtr_clr_list(char **texture_path, int texture_len);
int			is_valid_texture_or_color(char *current_line);
int			verify_element_dup(t_cub *info);

int			check_colors(char **texture_paths);
int			commas_qntt(char *colors);
int			is_valid_color_format(char *current_line);
int			validate_line_content(char *current_line);
int			check_line_start_validity(char *current_line);
int			check_and_update_flag(char **current_line, int *flag);

int			valid_map_boundaries(char **raw_map_data);
int			is_boundered_by_walls(char *current_line);
int			validate_map_line(char *current_line, int *char_count);

char		*fetch_final_map_line(char **raw_map_data);
int			is_line_bordered_by_one(char *current_line);
int			validate_map_edges(char **raw_map_data);

int			check_and_format_map(t_cub *info);
int			validate_square_map(t_cub *info);
int			find_max_line_length(char **raw_map_data);
int			count_map_lines(char **raw_map_data);
int			initialize_square_map(t_cub *info, int max_line_size);
int			check_horizontal_walls(char **raw_map_data);
int			check_vertical_walls(char **raw_map_data);
char		*pad_map_line(char *current_line, int max_line_size);

#endif
