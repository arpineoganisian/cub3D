/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:58:43 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:49:30 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keycode_left(t_head *h)
{
	h->player.old_dir_x = h->player.dir_x;
	h->player.dir_x = h->player.dir_x * cos(-ROTATION) -
		h->player.dir_y * sin(-ROTATION);
	h->player.dir_y = h->player.old_dir_x * sin(-ROTATION) +
		h->player.dir_y * cos(-ROTATION);
	h->ray.old_plane_x = h->ray.plane_x;
	h->ray.plane_x = h->ray.plane_x * cos(-ROTATION) -
		h->ray.plane_y * sin(-ROTATION);
	h->ray.plane_y = h->ray.old_plane_x * sin(-ROTATION) +
		h->ray.plane_y * cos(-ROTATION);
}

void	keycode_right(t_head *h)
{
	h->player.old_dir_x = h->player.dir_x;
	h->player.dir_x = h->player.dir_x * cos(ROTATION)
		- h->player.dir_y * sin(ROTATION);
	h->player.dir_y = h->player.old_dir_x * sin(ROTATION)
		+ h->player.dir_y * cos(ROTATION);
	h->ray.old_plane_x = h->ray.plane_x;
	h->ray.plane_x = h->ray.plane_x * cos(ROTATION)
		- h->ray.plane_y * sin(ROTATION);
	h->ray.plane_y = h->ray.old_plane_x * sin(ROTATION)
		+ h->ray.plane_y * cos(ROTATION);
}
