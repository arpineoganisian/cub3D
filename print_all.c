/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:05:57 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/19 20:37:55 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_struct *h)
{
	int i;
	int j;

	j = h->start_map;
	while (h->s[j])
	{
		i = 0;
		while (h->s[j][i])
		{
			if (h->s[j][i] == '1')
				print_square(h, i, j-h->start_map, 0xc8d4e8);
			i++;
		}
		j++;
	}
}

void	print_square(t_struct *h, int i, int j, unsigned int color)
{
	int	x1;
	int	y1;

	h->map.x = i * SCALE;
	h->map.y = j * SCALE;
	x1 = h->map.x + SCALE;
	y1 = h->map.y + SCALE;
	while (h->map.y < y1)
	{
		h->map.x = i * SCALE;
		while (h->map.x < x1)
		{
			my_pixel_put(h, h->map.x, h->map.y, color);
			h->map.x++;
		}
		h->map.y++;
	}
}

void	print_wall(t_struct *h, float ray_len, t_player *ray, int x)
{
	int 	wall_height;
	float	wall_pos;
	int		y;

	(void)ray;
	y = 0;
	wall_height = h->resol.ry / ray_len;
	wall_pos = h->resol.ry / 2 - wall_height / 2;

	while(y < h->resol.ry)
	{
		if(y >= wall_pos && y < (wall_pos + wall_height))
			my_pixel_put(h, x, y, 0xBF9EF9);
		// else 
		// {
		// 	if(y < wall_pos)
		// 		my_pixel_put(h, x, y, h->color.ceiling_color);
		// 	else
		// 		my_pixel_put(h, x, y, h->color.floor_color);
		//}
		y++;
	}

}

void	print_ray(t_struct *h)
{
	t_player	ray;
	float		ray_len;
	int			x;

	x = 0;
	ray = h->player;
	ray.start = ray.dir - (M_PI / 6);
	ray.end = ray.dir + (M_PI / 6);

	while (ray.start <= ray.end)
	{
		ray.px = h->player.px;
		ray.py = h->player.py;
		while (h->s[(int)(ray.py + h->start_map)][(int)(ray.px)] != '1')
		{
			ray.px += cos(ray.start) / SCALE;
			ray.py -= sin(ray.start) / SCALE;
			my_pixel_put(h, (ray.px * SCALE), (ray.py * SCALE), 0x55F294);
		}
		ray_len = hypot(fabs(h->player.py - ray.py), fabs(h->player.px - ray.px));
		//printf("%f\n", ray_len);
		print_wall(h, ray_len, &ray, x);
		ray.start += (M_PI / 6) / h->resol.rx;
		x++;
	}
}

void	print_all(t_struct *h)
{
	h->mnlbx.mlx = mlx_init();
	h->mnlbx.mlx_win = mlx_new_window(h->mnlbx.mlx, h->resol.rx, h->resol.ry, "cub3D");
	h->data.img = mlx_new_image(h->mnlbx.mlx, h->resol.rx, h->resol.ry);
	h->data.addr = mlx_get_data_addr(h->data.img, &h->data.bpp, &h->data.line_length, &h->data.endian);

	parse_player(h);

	print_map(h);
	print_square(h, h->player.px, h->player.py, 0xFFFFFF);
	print_ray(h);

	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);

	mlx_hook(h->mnlbx.mlx_win, 2, 1L<<0, move, h);
	mlx_hook(h->mnlbx.mlx_win, 17, 0, x_close, 0);

	mlx_loop(h->mnlbx.mlx);
}