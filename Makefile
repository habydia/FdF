# Variables
cc = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c window.c image.c
OBJ = $(SRC:.c=.o)
NAME = fdf

all: $(NAME)

# Dossier et librairie MiniLibX
MLX_DIR = mlx_linux
MLX_LIB = $(MLX_DIR)/*_Linux.a

# Compilation du programme principal
$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(OBJ) -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

# Compilation de MiniLibX
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I$(MLX_DIR) -O3 -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
re: all clean fclean re 