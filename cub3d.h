/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:55:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/21 01:08:24 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close
# include <stdlib.h> // malloc

# include <stdio.h> // УДАЛИТЬ

#define SCALE 15

typedef struct 	s_mnlbx
{
	void	*mlx;
	void	*mlx_win;
}				t_mnlbx;

typedef struct	s_data
{
	void	*img; // открывает файл и достает в image
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian; //порядок байтов
}				t_data;

typedef struct	s_resolution
{
	int	x;
	int	y;
}				t_resolution;

typedef struct	s_color
{
	int	ceiling_color;
	int	floor_color;
}				t_color;

////структура для 2д карты
// typedef struct	s_map
// {
// 	int	x;
// 	int	y;
// }				t_map;

typedef struct	s_player
{
	double	x;
	double	y;
	double	dir_x; //направление игрока, т.е. в какую сторону он будет смещаться по х и у
	double	dir_y; //направление игрока, т.е. в какую сторону он будет смещаться по х и у
}				t_player;

typedef struct	s_ray
{
	double	cam_x;
	double	plane_x; //плоскость камеры игрока, перпендекулярная dir
	double	plane_y; 
	
	double	raydir_x; //направление луча
	double	raydir_y;
	
	double	first_side_x; //расстрояние от старта до первой стороны х или у
	double	first_side_y;

	double	delta_x; //дельта 
	double	delta_y;

}				t_ray;

typedef struct	s_head
{
	char			**map;
	int				start_map;
	t_mnlbx			mnlbx;
	t_resolution	resol;
//	t_map			map;
	t_player		player;
	t_data			data;
	t_color			color;
	t_ray			ray;
}				t_head;

int		main(int argc, char **argv);
void	parse_player(t_head *head);
void	render_all(t_head *h);
//void	print_map(t_struct *h);
//void	print_square(t_struct *h, int i, int j, unsigned int color);
//void	print_ray(t_struct *h);
int		move(int keycode, t_head *h);
void	my_pixel_put(t_head *h, int x, int y, int color);
int		x_close();

#endif
