
#using the mlx library as submodule
#LIBMLX	:=	./MLX42
#LIBS	:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
#MLX_URL = https://github.com/codam-coding-college/MLX42.git

#INC		:=	-I $(LIBMLX)/include

#all: libmlx $(NAME)

#libmlx:
#@echo "Making MLX42..."
#@git clone $(MLX_URL)
#@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4


NAME = cub3d
LIBFT = libft
LIBFT_A = libft/libft.a

MLX = MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -O3 -ffast-math

OBJS = $(SRC:%.c=%.o)

SRC = src/load_map.c src/map_cheking.c src/colors_checking.c \
      src/walls_checking.c src/raws_map_check.c src/format_map.c \
      src/texture_list_parser.c src/colors_texture.c \
      src/get_position.c src/game_loop/game_loop.c src/game_loop/keys.c	\
      src/photon_trajectory.c src/game_loop/player_mov.c src/main.c get_next_line/get_next_line.c \
	  src/rendering_walls.c src/colors_checking1.c src/format_map1.c src/load_map1.c \
	  src/texture_list_parser1.c \

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling cub3D ..."
	@make -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(OBJS) $(LIBFT_A) $(MLX) -o $(NAME)

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

re: fclean all
