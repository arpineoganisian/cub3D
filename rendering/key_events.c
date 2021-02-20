/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:50:02 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:55:03 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_window(t_head *h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h->resol.h)
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

int		move(t_head *h)
{
	clean_window(h);
	if (h->key.w)
		keycode_w(h);
	if (h->key.s)
		keycode_s(h);
	if (h->key.a)
		keycode_a(h);
	if (h->key.d)
		keycode_d(h);
	if (h->key.left)
		keycode_left(h);
	if (h->key.right)
		keycode_right(h);
	if (h->key.esc)
	{
		mlx_destroy_window(h->mnlbx.mlx, h->mnlbx.mlx_win);
		free_mem(h);
		exit(0);
	}
	draw_wall(h);
	draw_sprites(h);
	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win,
		h->data.img, 0, 0);
	return (0);
}

int		x_close(t_head *h)
{
	free_mem(h);
	exit(0);
}
