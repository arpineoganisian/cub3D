# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 19:47:02 by hwoodwri          #+#    #+#              #
#    Updated: 2021/02/12 19:43:04 by hwoodwri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3d.h
HEADER_DIR = ./includes/

MLX = -lmlx libmlx.dylib -framework OpenGL -framework AppKit

LIBFT = libft.a
LIBFT_DIR = ./libft/

SRC = ./parsing/main.c \
	./parsing/parser.c \
	./parsing/parse_resolution.c \
	./parsing/parse_textures.c\
	./parsing/parse_colors.c \
	./parsing/parse_player.c \
	./parsing/parse_sprites.c \
	./parsing/map_validation.c \
	./rendering/render_all.c \
	./rendering/init_mlx.c \
	./rendering/draw_wall_utils01.c \
	./rendering/draw_wall_utils02.c \
	./rendering/draw_sprite_utils01.c \
	./rendering/draw_sprite_utils02.c \
	./rendering/render_utils.c \
	./rendering/key_press_release.c \
	./rendering/key_events.c \
	./rendering/keycode_move.c \
	./rendering/keycode_rotation.c \
	./rendering/screenshot.c \
	./handling_errors/error_mssg.c \

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -I $(HEADER_DIR) $< -o $@
	
clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
