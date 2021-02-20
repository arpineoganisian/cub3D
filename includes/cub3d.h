/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:55:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:29:52 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define ESC 53
# define W 13
# define A 0
# define D 2
# define S 1
# define LEFT 123
# define RIGHT 124
# define ROTATION 0.05
# define MOVE 0.08

typedef struct	s_mnlbx
{
	void	*mlx;
	void	*mlx_win;
}				t_mnlbx;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_resolution
{
	int	w;
	int	h;
}				t_resolution;

typedef struct	s_color
{
	int	ceiling_color;
	int	floor_color;
}				t_color;

typedef struct	s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	old_dir_x;
}				t_player;

typedef struct	s_ray
{
	double	cam_y;
	double	plane_x;
	double	plane_y;
	double	old_plane_x;
	double	raydir_x;
	double	raydir_y;
	double	first_side_x;
	double	first_side_y;
	double	delta_x;
	double	delta_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	perp;
	int		side;
	double	*perp_buf;
}				t_ray;

typedef struct	s_wall
{
	int				height;
	int				start;
	int				end;
	int				ceiling;
	double			x;
	double			y;
	int				tex_x;
	int				tex_y;
	double			scale;
	unsigned int	color;
}				t_wall;

typedef struct	s_texture
{
	int		*img;
	char	*addr;
	char	*path;
	int		w;
	int		h;
	int		bpp;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct	s_sprite_buf
{
	double	x;
	double	y;
	double	dist;
}				t_sprite_buf;

typedef struct	s_sprite
{
	int				*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	char			*path;
	int				tex_w;
	int				tex_h;
	int				num;
	t_sprite_buf	*buf;
	double			current_x;
	double			current_y;
	double			inv;
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
}				t_sprite;

typedef struct	s_save
{
	int	flag;
	int	fd;
}				t_save;

typedef struct	s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}				t_key;

typedef struct	s_head
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
	int				r;
	int				s;
	char			*tmp_str;
	char			**map;
	int				end_map;
	t_mnlbx			mnlbx;
	t_resolution	resol;
	t_player		player;
	t_data			data;
	t_color			color;
	t_ray			ray;
	t_wall			wall;
	t_texture		tex_n;
	t_texture		tex_s;
	t_texture		tex_w;
	t_texture		tex_e;
	t_texture		current_tex;
	t_sprite		sprite;
	t_save			save;
	t_key			key;
}				t_head;

int				main(int argc, char **argv);
void			parser(t_head *h, int j);
void			parse_player(t_head *h);
void			parse_resolution(t_head *h, char *s);
void			parse_textures(t_head *h, char *s, char side);
void			parse_sprite_tex(t_head *h, char *s);
void			parse_sprite_pos(t_head *h);
void			parse_colors(t_head *h, char *s, char c);
void			map_valid(t_head *h);
void			init_mlx(t_head *h);
void			max_screen_size(t_head *h);
void			init_mlx(t_head *h);
void			init_wall_textures(t_head *h);
void			init_sprite_texture(t_head *h);
void			render_all(t_head *h);
void			draw_wall(t_head *h);
void			ray_dir_and_delta(t_head *h, int x);
void			first_side_ray_meet(t_head *h);
void			ray_hit(t_head *h);
void			fish_eye(t_head *h);
void			wall_params(t_head *h);
void			x_coord_of_hit(t_head *h);
void			choose_texture(t_head *h);
void			texture_calculations(t_head *h);
void			wall_draw_line(t_head *h, int x);
void			draw_sprites(t_head *h);
void			sort_sprites(t_head *h, double left, double right);
int				partitioning(double left, double right, t_head *h,
	t_sprite_buf *tmp);
void			calculate_dist_to_sprites(t_head *h, int i);
void			sprite_initial_calculations(t_head *h);
void			vertical_line(t_head *h);
void			horizontal_line(t_head *h);
void			sprite_draw_vertical_line(t_head *h);
void			sprite_draw_line(t_head *h);
int				key_press(int keycode, t_head *h);
int				key_release(int keycode, t_head *h);
int				move(t_head *h);
void			keycode_w(t_head *h);
void			keycode_s(t_head *h);
void			keycode_a(t_head *h);
void			keycode_d(t_head *h);
void			keycode_left(t_head *h);
void			keycode_right(t_head *h);
int				x_close();
void			screenshot(t_head *h);
void			my_pixel_put(t_head *h, int x, int y, int color);
unsigned int	tex_to_pix(t_texture *tex, int x, int y);
unsigned int	tex_to_pix_sprite(t_sprite *tex, int x, int y);
int				error_mssg(int err, t_head *h);
void			free_mem(t_head *h);

#endif
