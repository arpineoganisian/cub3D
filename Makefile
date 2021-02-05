# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 19:47:02 by hwoodwri          #+#    #+#              #
#    Updated: 2021/02/05 00:14:48 by hwoodwri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft.a

LIBFT_DIR = ./libft/

SRC = 

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I. -lmlx -framework OpenGL -framework AppKit

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	cp libft/libft.a ./cub3D
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	
%.o: %.c cub3D
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
