/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:51:59 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:51:31 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keycode_w(t_head *h)
{
	if (h->map[(int)(h->player.y
		+ h->player.dir_y * MOVE)][(int)h->player.x] != '1')
		h->player.y += h->player.dir_y * MOVE;
	if (h->map[(int)h->player.y][(int)(h->player.x
		+ h->player.dir_x * MOVE)] != '1')
		h->player.x += h->player.dir_x * MOVE;
}

void	keycode_s(t_head *h)
{
	if (h->map[(int)(h->player.y
		- h->player.dir_y * MOVE)][(int)h->player.x] != '1')
		h->player.y -= h->player.dir_y * MOVE;
	if (h->map[(int)h->player.y][(int)(h->player.x
		- h->player.dir_x * MOVE)] != '1')
		h->player.x -= h->player.dir_x * MOVE;
}

void	keycode_a(t_head *h)
{
	if (h->map[(int)(h->player.y
		- h->player.dir_x * MOVE)][(int)(h->player.x)] != '1')
		h->player.y -= h->player.dir_x * MOVE;
	if (h->map[(int)(h->player.y)][(int)(h->player.x
		+ h->player.dir_y * MOVE)] != '1')
		h->player.x += h->player.dir_y * MOVE;
}

void	keycode_d(t_head *h)
{
	if (h->map[(int)(h->player.y
		+ h->player.dir_x * MOVE)][(int)(h->player.x)] != '1')
		h->player.y += h->player.dir_x * MOVE;
	if (h->map[(int)(h->player.y)][(int)(h->player.x
		- h->player.dir_y * MOVE)] != '1')
		h->player.x -= h->player.dir_y * MOVE;
}
