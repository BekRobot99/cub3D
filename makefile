NAME = cub3d
LIBFT = libft
LIBFT_A = libft/libft.a

MLX_DIR = MLX42
MLX = $(MLX_DIR)/build/libmlx42.a
MLX_URL = https://github.com/codam-coding-college/MLX42.git
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -O3 -ffast-math

OBJS = $(SRC:%.c=%.o)

SRC = src/map_parser/load_map.c src/map_parser/map_cheking.c src/map_parser/colors_checking.c \
      src/map_parser/walls_checking.c src/map_parser/raws_map_check.c src/map_parser/format_map.c \
      src/map_parser/texture_list_parser.c src/map_parser/colors_texture.c \
      src/map_parser/get_position.c src/game_loop/game_loop.c src/game_loop/keys.c \
      src/game_loop/photon_trajectory.c src/game_loop/player_mov.c src/main.c get_next_line/get_next_line.c \
      src/game_loop/rendering_walls.c src/map_parser/colors_checking1.c src/map_parser/format_map1.c src/map_parser/load_map1.c \
      src/map_parser/texture_list_parser1.c src/map_parser/create_texture.c src/game_loop/init_game_loop.c \
      src/game_loop/mov_rot.c src/game_loop/rendering_walls1.c src/game_loop/photon1.c src/game_loop/photon2.c \
      src/game_loop/photon3.c

all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling cub3D ..."
	@make -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(OBJS) $(LIBFT_A) $(MLX) -o $(NAME)

$(MLX):
	@echo "Cloning MLX42..."
	@if [ ! -d "$(MLX_DIR)" ]; then git clone $(MLX_URL) $(MLX_DIR); fi
	@echo "Building MLX42..."
	@cd $(MLX_DIR) && cmake -B build
	@cd $(MLX_DIR) && cmake --build build -j4

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@make clean -s -C $(LIBFT)
	@$(RM) $(OBJS)

fclean: clean
	@echo "Cleaning cube3D"
	@make fclean -s -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "Cleaning MLX42..."
	@if [ -d "$(MLX_DIR)/build" ]; then $(RM) -r $(MLX_DIR)/build; fi

re: fclean all