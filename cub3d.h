/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:55:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/17 16:27:54 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close
# include <stdlib.h> // malloc

# include <stdio.h> // УДАЛИТЬ

#define SCALE 20

typedef struct 	s_mnlbx
{
	void	*mlx;
	void	*mlx_win;
}				t_mnlbx;

typedef struct	s_resolution
{
	int	rx;
	int	ry;
}				t_resolution;

//структура для 2д карты
typedef struct	s_map
{
	int	x;
	int	y;
}				t_map;
////////////

typedef struct	s_player
{
	float	px;
	float	py;
	float	dir;
}				t_player;

typedef struct	s_data
{
	void	*img; // открывает файл и достает в image
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian; //порядок байтов
}				t_data;

typedef struct	s_struct
{
	char			**s;
	int				start_map;
	t_mnlbx			mnlbx;
	t_resolution	resol;
	t_map			map;
	t_player		player;
	t_data			data;
}					t_struct;

int		main(int argc, char **argv);
void	parse_player(t_struct *h);
void	print_all(t_struct *h);
void	print_map(t_struct *h);
void	print_square(t_struct *h, int i, int j, unsigned int color);
int		move(int keycode, t_struct *h);
void	my_pixel_put(t_struct *h, int x, int y, int color);
int		x_close();
void	print_ray(t_struct *h);

#endif
