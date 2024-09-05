
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
LIBFT = libft/libft.a
SRC = src/load_map.c src/map_cheking.c src/colors_checking.c \
      src/walls_checking.c src/raws_map_check.c src/format_map.c \
      src/texture_list_parser.c src/colors_texture.c \
      src/get_position.c src/game_loop/game_loop.c src/game_loop/keys.c \
      src/photon_trajectory.c src/game_loop/player_mov.c src/main.c get_next_line/get_next_line.c 

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I./MLX42/MLX42/include -I./libft
LDFLAGS = -L./MLX42/MLX42/build -lmlx42 -lglfw -lm -L./libft -lft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compiling libft"
	@$(MAKE) -C libft

$(NAME): $(OBJS)
	@echo "Linking $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files"
	rm -f $(OBJS)
	@$(MAKE) -C libft clean

fclean: clean
	@echo "Cleaning $(NAME) and libft"
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re