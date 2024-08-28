
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
SRC = #  Add sources here
		  
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra 
FLAGS = -lmlx -framework OpenGL -framework AppKit 
INCLUDE = ./include/cub3d.h ./libft/libft.h


OBJS = $(SRC:.c=.o)

all : $(LIBFT) $(NAME)	
	
$(LIBFT):
	@make -C libft

$(NAME) :$(OBJS) $(LIBFT) $(INCLUDE)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)  -Llibft -lft
	
clean:
	@$(RM) $(OBJS) $(OBJB) 
	@make clean -C libft 

fclean : clean
	@$(RM) $(NAME) $(LIBFT)
re: fclean all