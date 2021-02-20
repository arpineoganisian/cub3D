/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 00:53:25 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:53:41 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_head *h)
{
	if (keycode == W)
		h->key.w = 1;
	if (keycode == S)
		h->key.s = 1;
	if (keycode == A)
		h->key.a = 1;
	if (keycode == D)
		h->key.d = 1;
	if (keycode == LEFT)
		h->key.left = 1;
	if (keycode == RIGHT)
		h->key.right = 1;
	if (keycode == ESC)
		h->key.esc = 1;
	return (0);
}

int	key_release(int keycode, t_head *h)
{
	if (keycode == W)
		h->key.w = 0;
	if (keycode == S)
		h->key.s = 0;
	if (keycode == A)
		h->key.a = 0;
	if (keycode == D)
		h->key.d = 0;
	if (keycode == LEFT)
		h->key.left = 0;
	if (keycode == RIGHT)
		h->key.right = 0;
	return (0);
}
