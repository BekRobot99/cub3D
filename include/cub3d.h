/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:07 by abekri            #+#    #+#             */
/*   Updated: 2024/09/02 03:17:17 by abekri           ###   ########.fr       */
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

# define 	BUFFER_SIZE 42
#define 	FOV 70
#define 	HEIGHT 1080
#define 	WIDTH 1920

//preparing thr structs for the game
typedef struct s_gamer
{
	int		move_lt_rt;// Movement along the left-right axis
	int		move_up_dwn;// Movment along the up-down axis (forward/backward)
	int		mouse_x;// Current mouse x-coordinate
	int		mouse_y;// Curent mouse y-coordinate
	int		pos_x;// Player's x-coordinate on the map
	int		pos_y;// Player's y-coordinate on the map
	double	direction;// The angle (in radians) that the player is facing
	int		dir_rotation;// Direction of rotation (-1 for left, 1 for right)
	float	fov;// Field of view; defines how wide the player's vision is
} t_gamer;


typedef struct s_castray
{
	double	intrsxn_x_vert;// X-coordinate of the vertical intersection point of the ray
	double	intrsxn_y_vert;// Y-coordinate of the vertical intersection point of the ray
	int		beam_index;// Index of the current ray being processed
	double	ray_length;// Length of the ray from the player to the wall
	int		hit_type;// Type of surface the ray hit (e.g., horizontal or vertical wall)
	double	beam_angle;// Angle of the ray relative to the player's direction
	double	intrsxn_x_horz;// X-cordinate of the horizontal intersetion point of the ray
	double	intrsxn_y_horz;// Y-coordinate of the horizontal intersecton point of the ray
} t_castray;


typedef struct s_graphics
{
	t_gamer				*player;        // Pointer to the player's data
	mlx_image_t			*image;         // The image buffer where the game's graphics are drawn before being displayed on the screen.
	mlx_t				*mlx_ptr;       // window creation, event management, and rendering.
	t_cub				*data;          // game's data to determining where walls are.
	t_texture			*texture;       // the textures used for walls, floor, ceiling, etc.; used to render the game world realistically.
	mouse_mode_t		mouse_mode;     // Stores the current mode of mouse input
	t_castray			*raycast;       // the raycasting data is used for rendering the 3D perspective from the 2D map data.
} t_graphics;


typedef struct s_texture
{
	char				*path;
	void				*img;
	char				*ident;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	struct s_texture	*next;
	int					width;
	int					height;
	mlx_texture_t		*so;
	mlx_texture_t		*no;
	mlx_texture_t		*ea;
	mlx_texture_t		*we;
}						t_texture;

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
	t_texture			*texture;
}						t_cub;

char					*get_next_line(int fd);

void					free_str_array(char *array[]);
void					cleanup_resources(char *texture_path,
							char *current_line, int fd);
int						validate_textures(t_cub *info, int texture_len);
int						is_valid_txtr_color(char *line);
int						open_file(char *file_path, t_cub *info);
int						read_first_line(t_cub *info);
int						process_lines(t_cub *info, int *texture_count);
int						load_map_data(char *file_path, t_cub *info,
							int *texture_len);

int						is_valid_cub_ext(char *filename);

int						parse_map_data(t_cub *info, int count);
char					*read_map_content(t_cub *info);
int						validate_txtr_clr_list(char **texture_path,
							int texture_len);
int						is_valid_texture_or_color(char *current_line);
int						verify_element_dup(t_cub *info);

int						check_colors(char **texture_paths);
int						commas_qntt(char *colors);
int						is_valid_color_format(char *current_line);
int						validate_line_content(char *current_line);
int						check_line_start_validity(char *current_line);
int						check_and_update_flag(char **current_line, int *flag);

int						valid_map_boundaries(char **raw_map_data);
int						is_boundered_by_walls(char *current_line);
int						validate_map_line(char *current_line, int *char_count);

char					*fetch_final_map_line(char **raw_map_data);
int						is_line_bordered_by_one(char *current_line);
int						validate_map_edges(char **raw_map_data);

int						check_and_format_map(t_cub *info);
int						validate_square_map(t_cub *info);
int						find_max_line_length(char **raw_map_data);
int						count_map_lines(char **raw_map_data);
int						initialize_square_map(t_cub *info, int max_line_size);
int						check_horizontal_walls(char **raw_map_data);
int						check_vertical_walls(char **raw_map_data);
char					*pad_map_line(char *current_line, int max_line_size);

void					free_texture_list(t_texture **list_head);
void					cleanup_map_data(t_cub *info);
int						build_texture_list(t_cub *info,
							t_texture **texture_list);

int						process_texture_colors(t_cub *info,
							t_texture *texture_list);

void					find_player_position(t_cub *info);
void					calculate_map_dimensions(t_cub *info);

int						init_game_loop(t_graphics *graf);
int			init_textures(t_texture *texture, t_texture *texture_list);
int						valid_txtr_paths(t_texture *texture_list);

#endif