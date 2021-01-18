/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:05:57 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/18 17:44:45 by hwoodwri         ###   ########.fr       */
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

void	print_ray(t_struct *h)
{
	t_player ray;

	ray = h->player;
	ray.px = h->player.px;
	ray.py = h->player.py;
	printf("%f\n", h->player.px);
	while (h->s[(int)(ray.py + h->start_map)][(int)(ray.px)] != '1')
	{
		ray.px += cos(ray.dir) / SCALE;
		ray.py -= sin(ray.dir) / SCALE;
		my_pixel_put(h, (ray.px * SCALE), (ray.py * SCALE), 0x55F294);
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