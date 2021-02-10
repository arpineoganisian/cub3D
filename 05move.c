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

void ft_clean_window(t_head *h)
{
	int	i;
	int	j;

	i = 0;
	while(i < h->resol.h)
	{
		j = 0;
		while (j < h->resol.w)
		{
			my_pixel_put(h, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int move(int keycode, t_head *h)
 {
	//printf("%d\n", keycode);

	ft_clean_window(h);
	if (keycode == W)
	{
		if (h->map[(int)(h->player.y + h->player.dir_y * MOVE)][(int)h->player.x] != '1') 
		// && h->map[(int)(h->player.y + h->player.dir_y * MOVE)][(int)h->player.x] != '2')
			h->player.y += h->player.dir_y * MOVE;
		if (h->map[(int)h->player.y][(int)(h->player.x + h->player.dir_x * MOVE)] != '1')
		// &&	h->map[(int)h->player.y][(int)(h->player.x + h->player.dir_x * MOVE)] != '2')
			h->player.x += h->player.dir_x * MOVE;
	}
	if (keycode == S)
	{
		if (h->map[(int)(h->player.y - h->player.dir_y * MOVE)][(int)h->player.x] != '1') 
			// && h->map[(int)(h->player.y - h->player.dir_y * MOVE)][(int)h->player.x] != '2')
			h->player.y -= h->player.dir_y * MOVE;
		if (h->map[(int)h->player.y][(int)(h->player.x - h->player.dir_x * MOVE)] != '1') 
			//&& h->map[(int)h->player.y][(int)(h->player.x - h->player.dir_x * MOVE)] != '2') 
			h->player.x -= h->player.dir_x * MOVE;
	}
	if (keycode == A)
	{
		if (h->map[(int)(h->player.y - h->player.dir_x * MOVE)][(int)(h->player.x + h->player.dir_y * MOVE)] != '1')
			//  &&	h->map[(int)(h->player.y - h->player.dir_x * MOVE)][(int)(h->player.x + h->player.dir_y * MOVE)] != '2')
		{
			h->player.y -= h->player.dir_x * MOVE;
			h->player.x += h->player.dir_y * MOVE;
		}
	}
	if (keycode == D)
	{
		if (h->map[(int)(h->player.y + h->player.dir_x * MOVE)][(int)(h->player.x - h->player.dir_y * MOVE)] != '1') 
			// && h->map[(int)(h->player.y + h->player.dir_x * MOVE)][(int)(h->player.x - h->player.dir_y * MOVE)] != '2')
		{
			h->player.x -= h->player.dir_y * MOVE;
			h->player.y += h->player.dir_x * MOVE;
		}
	}
	if (keycode == LEFT)
	{
		h->player.old_dir_x = h->player.dir_x;
		h->player.dir_x = h->player.dir_x * cos(-ROTATION) - h->player.dir_y * sin(-ROTATION);
		h->player.dir_y = h->player.old_dir_x * sin(-ROTATION) + h->player.dir_y * cos(-ROTATION);
		h->ray.old_plane_x = h->ray.plane_x;
		h->ray.plane_x = h->ray.plane_x * cos(-ROTATION) - h->ray.plane_y * sin(-ROTATION);
		h->ray.plane_y = h->ray.old_plane_x * sin(-ROTATION) + h->ray.plane_y * cos(-ROTATION);
	}
	if (keycode == RIGHT)
	{
		h->player.old_dir_x = h->player.dir_x;
		h->player.dir_x = h->player.dir_x * cos(ROTATION) - h->player.dir_y * sin(ROTATION);
		h->player.dir_y = h->player.old_dir_x * sin(ROTATION) + h->player.dir_y * cos(ROTATION);
		h->ray.old_plane_x = h->ray.plane_x;
		h->ray.plane_x = h->ray.plane_x * cos(ROTATION) - h->ray.plane_y * sin(ROTATION);
		h->ray.plane_y = h->ray.old_plane_x * sin(ROTATION) + h->ray.plane_y * cos(ROTATION);
	}
	if (keycode == ESC)
	{
		mlx_destroy_window(h->mnlbx.mlx, h->mnlbx.mlx_win);
		exit(0);
	}
	draw_wall(h);
	draw_sprites(h);
	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);
	
	return (0);
}

int x_close()
{
	exit(0);
}