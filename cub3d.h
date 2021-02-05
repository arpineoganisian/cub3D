/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:55:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/05 20:41:46 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close
# include <stdlib.h> // malloc

# include <stdio.h> // УДАЛИТЬ

#define ESC 53
#define W 13
#define A 0
#define D 2
#define S 1
#define ROTATION 0.05
#define MOVE 0.1
#define LEFT 123
#define RIGHT 124

typedef struct 	s_mnlbx
{
	void	*mlx;
	void	*mlx_win;
}				t_mnlbx;

typedef struct	s_data
{
	void	*img; //открывает файл и достает в image
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
	double	dir_y; 
	double	old_dir_x; // для вращения
}				t_player;

typedef struct	s_ray
{
	double	cam_y;
	double	plane_x; //плоскость камеры игрока, перпендекулярная dir
	double	plane_y;
	double	old_plane_x; // для вращения
	
	double	raydir_x; //направление луча
	double	raydir_y;
	
	double	first_side_x; //расстрояние от старта до первой стороны х или у
	double	first_side_y;

	double	delta_x; //дельта 
	double	delta_y;

	int		map_x; //в какой клеточке находится луч
	int		map_y;

	int		step_x;
	int		step_y;

	double	perp; //перпендикуляр

	int		side; //последний сдвиг по x или y (с какой стороны граница стены)
	double	*perp_buf;

}				t_ray;

typedef struct	s_wall
{
	int				height;
	int				start;
	int				end;
	int				ceiling;

	double			x; //wallX - точное значение места удара о стену
	double			y; //texPos
	int				tex_x; //какую именно координату по х берем из текстуры
	int				tex_y;
	double			scale; //насколько увеличиваем координату текстуры на пиксель экрана
	unsigned int	color;
}				t_wall;

typedef struct	s_texture
{	
	int		*img; //сама картинка с текстурой
	char	*addr;
    
	char    *path;
    int     x;
    int     y;

	int		bpp;
	int		line_length;
	int		endian; //порядок байтов
}				t_texture;


typedef struct	s_sprite_buf
{
	double	x; //массив координат по x
	double	y; //массив координат по у
	double	dist; //расстояние от игрока до спрайта
}				t_sprite_buf;

typedef struct		s_sprite
{	
	int				*img; //сама картинка с текстурой
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian; //порядок байтов
	
	char			*path;
    int				tex_w; //ширина текстуры 
    int				tex_h; //высота текстуры
	
	int				num;
	t_sprite_buf	*buf;

	double			current_x;
	double			current_y;
	double			inv; //inversion, без нее спрайты становятся больше/меньше при удалении/приближении
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;

	int				height;
	int				width;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
}					t_sprite;

typedef struct	s_save
{
	int	flag;
	int	fd;
}				t_save;

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
	t_wall			wall;
	t_texture		tex_n;
	t_texture		tex_s;
	t_texture		tex_w;
	t_texture		tex_e;
	t_texture		current_tex; //текущая текстура (чтобы работало с разными размерами текстур)
	t_sprite		sprite;
	t_save			save;
}				t_head;

int				main(int argc, char **argv);
int				check_arguments(int argc, char **argv, t_head *h);
void			parser(t_head *h);
void				parse_resolution(t_head *h, char *s);
void			parse_sprite_pos(t_head *h);
void			parse_sprite_tex(t_head *h, char *s);
int				parse_textures(t_head *h, char *s, char side);
void				parse_colors(t_head *h, char *s, char c);
void			parse_player(t_head *h);
int				create_rgb(int r, int g, int b);
void			allocate_mem(t_head *h);



void			render_all(t_head *h);
void			draw_wall(t_head *h);
int				move(int keycode, t_head *h);
void			my_pixel_put(t_head *h, int x, int y, int color);
int				x_close();
unsigned int	tex_to_pix(t_texture *tex, int x, int y);
unsigned int	tex_to_pix_sprite(t_sprite *tex, int x, int y);
void			draw_sprites(t_head *h);
int				error_mssg(int err);
void			screenshot(t_head *h);


#endif
