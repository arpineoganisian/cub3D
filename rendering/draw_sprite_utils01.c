/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:15:24 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:53:07 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		partitioning(double left, double right, t_head *h, t_sprite_buf *tmp)
{
	while ((h->sprite.buf[(int)right].dist <= tmp->dist) && (left < right))
		right--;
	if (left != right)
	{
		h->sprite.buf[(int)left] = h->sprite.buf[(int)right];
		left++;
	}
	while ((h->sprite.buf[(int)left].dist >= tmp->dist) && (left < right))
		left++;
	if (left != right)
	{
		h->sprite.buf[(int)right] = h->sprite.buf[(int)left];
		right--;
	}
	return (left);
}

void	sort_sprites(t_head *h, double left, double right)
{
	int				l_hold;
	int				r_hold;
	t_sprite_buf	tmp;

	l_hold = left;
	r_hold = right;
	tmp = h->sprite.buf[(int)left];
	if (left < right)
		left = partitioning(left, right, h, &tmp);
	h->sprite.buf[(int)left] = tmp;
	tmp.dist = left;
	left = l_hold;
	right = r_hold;
	if (left < tmp.dist)
		sort_sprites(h, left, tmp.dist - 1);
	if (right > tmp.dist)
		sort_sprites(h, tmp.dist + 1, right);
}

void	calculate_dist_to_sprites(t_head *h, int i)
{
	while (i < h->sprite.num)
	{
		h->sprite.buf[i].dist = pow((h->player.x - h->sprite.buf[i].x), 2) +
			pow((h->player.y - h->sprite.buf[i].y), 2);
		i++;
	}
}
