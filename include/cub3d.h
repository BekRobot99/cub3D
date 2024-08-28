/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:07 by abekri            #+#    #+#             */
/*   Updated: 2024/08/28 21:25:22 by abekri           ###   ########.fr       */
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
	int					fd;
	int					index;
	char				**map_grid;
	int					ppos_x;
	int					ppos_y;
	int					map_width;
	int					map_height;
	int					nb_lines;
	int					nb_cols;
	char				**texture_paths;
	char				**square_map;
	char				*texture_path;
	char				*raw_map_data;
	char				**rgb;
	char				**floor_clr;
	char				**ceiling_clr;
	char				*current_line;
}						t_cub;

char					*get_next_line(int fd);

#endif
