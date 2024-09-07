/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:07:07 by abekri            #+#    #+#             */
/*   Updated: 2024/09/07 07:38:57 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
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
# define FOV 70
# define HEIGHT 1080
# define WIDTH 1920
# define MAP_BLOCK_LEN 64

typedef struct s_steps
{
	double				x_step;
	double				y_step;
}						t_steps;

// preparing thr structs for the game
typedef struct s_gamer
{
	int					move_lt_rt;
	int					move_up_dwn;
	int					mouse_x;
	int					mouse_y;
	int					pos_x;
	int					pos_y;
	double				direction;
	int					dir_rotation;
	float				fov;
}						t_gamer;

typedef struct s_castray
{
	double				intrsxn_x_vert;
	double				intrsxn_y_vert;
	int					beam_index;
	double				ray_length;
	int					hit_type;
	double				beam_angle;
	double				intrsxn_x_horz;
	double				intrsxn_y_horz;
}						t_castray;

typedef struct s_texture
{
	char				*path;
	void				*img;
	char				*ident;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	mlx_texture_t		*texture;
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
	uint32_t			ceiling_color;
	uint32_t			floor_color;
}						t_cub;

typedef struct s_graphics
{
	t_gamer				*player;
	mlx_image_t			*image;
	mlx_t				*mlx_ptr;
	t_cub				*data;
	t_texture			*texture;
	mouse_mode_t		mouse_mode;
	t_castray			*raycast;
}						t_graphics;
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
int						init_textures(t_texture *texture,
							t_texture *texture_list);
int						valid_txtr_paths(t_texture *texture_list);

void					ft_exit(t_graphics *graf);

void					handle_key_event(mlx_key_data_t indent_info,
							void *graphics);

void					emit_photon_array(t_graphics *quanta_field);
double					trace_photon_path(t_graphics *quanta_field);
double					calculate_euclidean_norm(mlx_texture_t *texture,
							t_graphics *mlx);
double					quantum_phase_shift(double phase);

void					ft_delete_tex(t_texture *texture);
void					draw_game(void *mlxl);
int						file_exists(const char *path);
void					display_ray(t_graphics *graphics, int ray_index);
float					analyze_planar_intersections(t_graphics *quanta_field,
							float quantum_state);
float					analyze_axial_intersections(t_graphics *quanta_field,
							float quantum_state);

void					draw_wall(t_graphics *mlx, int t_pix, int b_pix,
							double wall_h);
void					place_pixel(t_graphics *graphics, int pos_x, int pos_y,
							int color_value);
int						skip_whitespace(char *current_line, int start_index);
int						is_valid_png_path(const char *path);
t_texture				*create_texture(char *path);
t_texture				*allocate_texture(void);
int						init_graphics(t_graphics *graf);
void					update_player_position(t_graphics *graf,
							double offset_x, double offset_y);
void					adjust_player_rotation(t_graphics *graf, int angle_pos);
#endif
