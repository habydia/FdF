# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 14:40:16 by hadia             #+#    #+#              #
#    Updated: 2025/03/28 16:48:27 by hadia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc

CFLAGS=	-Wall -Werror -Wextra -I.

SRC= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
     ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c\
	 ft_strcat.c ft_strcpy.c ft_strncpy.c\
     ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c ft_atoi.c\
     ft_strjoin.c ft_strtrim.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
     ft_memcmp.c ft_strnstr.c ft_strdup.c ft_calloc.c\
     ft_substr.c ft_strjoin.c ft_strtrim.c ft_free_split.c\
     ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
     ft_strmapi.c ft_striteri.c ft_putnbr_fd.c ft_split.c ft_itoa.c
SRC_BONUS= ft_lstnew_bonus.c ft_lstadd_front_bonus.c\
	   ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
	   ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\

HEADER= libft.h

SRC_ALL= $(SRC) $(SRC_BONUS)

OBJ=	$(SRC:.c=.o)

OBJ_ALL= $(SRC_ALL:.c=.o)

NAME=	libft.a

all: $(NAME)

$(NAME): $(OBJ) 
	ar -rcs $@ $^

bonus: $(OBJ_ALL)
	ar -rcs $(NAME) $(OBJ_ALL)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I .

clean: 
	rm -f $(OBJ) $(OBJ_ALL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re bonus
