# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 19:47:02 by hwoodwri          #+#    #+#              #
#    Updated: 2021/02/10 21:38:21 by hwoodwri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3d.h

MLX = -lmlx libmlx.dylib -framework OpenGL -framework AppKit

LIBFT = libft.a
LIBFT_DIR = ./libft/

SRC = 01init_zero.c \
	01main.c \
	02parse_elements1.c \
	02parse_elements2.c \
	03map_validation.c \
	04render_all.c \
	05move.c \
	06screenshot.c \
	07my_pixel_put.c \
	08error_mssg.c \
	09allocating_mem.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I.

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
