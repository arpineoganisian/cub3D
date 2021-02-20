/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:37:55 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:48:24 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	x_coord_of_hit(t_head *h)
{
	if (h->ray.side == 0)
		h->wall.x = h->player.y + h->ray.perp * h->ray.raydir_y;
	else
		h->wall.x = h->player.x + h->ray.perp * h->ray.raydir_x;
	h->wall.x -= floor(h->wall.x);
}

void	choose_texture(t_head *h)
{
	if (h->ray.side == 0 && h->player.x > h->ray.raydir_x + h->player.x)
		h->current_tex = h->tex_w;
	if (h->ray.side == 0 && h->player.x < h->ray.raydir_x + h->player.x)
		h->current_tex = h->tex_e;
	if (h->ray.side == 1 && h->player.y > h->ray.raydir_y + h->player.y)
		h->current_tex = h->tex_n;
	if (h->ray.side == 1 && h->player.y < h->ray.raydir_y + h->player.y)
		h->current_tex = h->tex_s;
}

void	texture_calculations(t_head *h)
{
	h->wall.tex_x = (int)(h->wall.x * h->current_tex.w);
	if ((h->ray.side == 0 && h->ray.raydir_x > 0) || (h->ray.side == 1 &&
		h->ray.raydir_y < 0))
		h->wall.tex_x = h->current_tex.w - h->wall.tex_x - 1;
	h->wall.scale = 1.0 * h->current_tex.h / h->wall.height;
	h->wall.y = (h->wall.start - h->resol.h / 2 + h->wall.height / 2) *
		h->wall.scale;
}

void	wall_draw_line(t_head *h, int x)
{
	while (h->wall.ceiling <= h->wall.start)
	{
		my_pixel_put(h, x, h->wall.ceiling, h->color.ceiling_color);
		h->wall.ceiling++;
	}
	while (h->wall.start <= h->wall.end)
	{
		h->wall.tex_y = (int)h->wall.y % (h->current_tex.w - 1);
		h->wall.y += h->wall.scale;
		h->wall.color = tex_to_pix(&h->current_tex, h->wall.tex_x,
		h->wall.tex_y);
		my_pixel_put(h, x, h->wall.start, h->wall.color);
		h->wall.start++;
	}
	while (h->wall.end < h->resol.h)
	{
		my_pixel_put(h, x, h->wall.end, h->color.floor_color);
		h->wall.end++;
	}
}
