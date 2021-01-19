/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:2.0:54 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/16 13:20:53 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_clean_window(t_struct *h)
{
	int	i;
	int	j;

	i = 0;
	while(i < h->resol.ry)
	{
		j = 0;
		while (j < h->resol.rx)
		{
			my_pixel_put(h, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int move(int keycode, t_struct *h)
 {
	//printf("%d\n", keycode);
	ft_clean_window(h);
	if (keycode == 13)
		h->player.py -= 1;
	if (keycode == 1)
		h->player.py += 1;
	if (keycode == 0)
		h->player.px -= 1;
	if (keycode == 2)
		h->player.px += 1;
	if (keycode == 123)
		h->player.dir += 0.05;
	if (keycode == 124)
		h->player.dir -= 0.05;
	if (keycode == 53)
	{
		mlx_destroy_window(h->mnlbx.mlx, h->mnlbx.mlx_win);
		exit(0);
	}
	print_map(h);
	print_square(h, h->player.px, h->player.py, 0xFFFFFF);
	print_ray(h);
	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);
	return (0);
}

int x_close()
{
	exit(0);
}