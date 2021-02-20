/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 01:32:48 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/11 03:03:32 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_dir_and_delta(t_head *h, int x)
{
	h->ray.cam_y = 2 * x / (double)h->resol.w - 1;
	h->ray.raydir_x = h->player.dir_x + h->ray.plane_x * h->ray.cam_y;
	h->ray.raydir_y = h->player.dir_y + h->ray.plane_y * h->ray.cam_y;
	h->ray.delta_x = fabs(1 / h->ray.raydir_x);
	h->ray.delta_y = fabs(1 / h->ray.raydir_y);
}

void	first_side_ray_meet(t_head *h)
{
	if (h->ray.raydir_x < 0)
	{
		h->ray.step_x = -1;
		h->ray.first_side_x = (h->player.x - h->ray.map_x) * h->ray.delta_x;
	}
	else
	{
		h->ray.step_x = 1;
		h->ray.first_side_x = (h->ray.map_x + 1.0 - h->player.x) *
			h->ray.delta_x;
	}
	if (h->ray.raydir_y < 0)
	{
		h->ray.step_y = -1;
		h->ray.first_side_y = (h->player.y - h->ray.map_y) * h->ray.delta_y;
	}
	else
	{
		h->ray.step_y = 1;
		h->ray.first_side_y = (h->ray.map_y + 1.0 - h->player.y) *
			h->ray.delta_y;
	}
}

void	ray_hit(t_head *h)
{
	while (h->map[h->ray.map_y][h->ray.map_x] != '1')
	{
		if (h->ray.first_side_x < h->ray.first_side_y)
		{
			h->ray.first_side_x += h->ray.delta_x;
			h->ray.map_x += h->ray.step_x;
			h->ray.side = 0;
		}
		else
		{
			h->ray.first_side_y += h->ray.delta_y;
			h->ray.map_y += h->ray.step_y;
			h->ray.side = 1;
		}
	}
}

void	fish_eye(t_head *h)
{
	if (h->ray.side == 0)
		h->ray.perp = (h->ray.map_x - h->player.x + (1 - h->ray.step_x) / 2)
			/ h->ray.raydir_x;
	else
		h->ray.perp = (h->ray.map_y - h->player.y + (1 - h->ray.step_y) / 2)
			/ h->ray.raydir_y;
}

void	wall_params(t_head *h)
{
	h->wall.height = (int)(h->resol.h / h->ray.perp);
	h->wall.start = -h->wall.height / 2 + h->resol.h / 2;
	h->wall.start < 0 ? (h->wall.start = 0) : 0;
	h->wall.end = h->wall.height / 2 + h->resol.h / 2;
	h->wall.end >= h->resol.h || h->wall.end < 0 ?
		(h->wall.end = h->resol.h - 1) : 0;
	h->wall.ceiling = 0;
}
