NAME = fdf

SRCS = main.c parse.c draw.c events.c get_next_line.c ft_fit_map_screen.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./mlx_linux -I./libft
LDFLAGS = -L./mlx_linux -lmlx -L./libft -lft -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	make -C ./mlx_linux
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	make -C ./mlx_linux clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re