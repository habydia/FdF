# filepath: /fdf/Makefile
# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRC = src/main.c src/graphics/draw.c src/graphics/graph_init.c \
src/parsing/parse.c src/utils/ft_get_next_line.c src/utils/ft_close_window.c \
src/events/key_hook.c src/events/mouse_hook.c \
src/math/project.c \
src/utils/ft_atoi_base.c

OBJ = $(SRC:.c=.o)
NAME = fdf

all: $(NAME)

# Dossier et librairie MiniLibX
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/*_Linux.a
LIB_DIR = libft
LIBFT = $(LIB_DIR)/libft.a
# Compilation du programme principal
$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT) Makefile
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX_DIR) -L$(LIB_DIR) -lmlx_Linux -lft -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

# Compilation de MiniLibX
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)
$(LIBFT):
	$(MAKE) -C $(LIB_DIR)
# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re