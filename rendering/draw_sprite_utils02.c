/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:03:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:49:55 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_initial_calculations(t_head *h)
{
	h->sprite.inv = 1.0 / (h->ray.plane_x * h->player.dir_y -
		h->player.dir_x * h->ray.plane_y);
	h->sprite.transform_x = h->sprite.inv * (h->player.dir_y *
		h->sprite.current_x - h->player.dir_x * h->sprite.current_y);
	h->sprite.transform_y = h->sprite.inv * (-h->ray.plane_y *
		h->sprite.current_x + h->ray.plane_x * h->sprite.current_y);
	h->sprite.screen_x = (int)(h->resol.w / 2 * (1 +
		h->sprite.transform_x / h->sprite.transform_y));
}

void	vertical_line(t_head *h)
{
	h->sprite.height = abs((int)(h->resol.h / h->sprite.transform_y));
	h->sprite.start_y = -h->sprite.height / 2 + h->resol.h / 2;
	h->sprite.start_y < 0 ? h->sprite.start_y = 0 : 0;
	h->sprite.end_y = h->sprite.height / 2 + h->resol.h / 2;
	h->sprite.end_y >= h->resol.h ? h->sprite.end_y = h->resol.h - 1 : 0;
}

void	horizontal_line(t_head *h)
{
	h->sprite.width = abs((int)(h->resol.h / h->sprite.transform_y));
	h->sprite.start_x = -h->sprite.width / 2 + h->sprite.screen_x;
	h->sprite.start_x < 0 ? h->sprite.start_x = 0 : 0;
	h->sprite.end_x = h->sprite.width / 2 + h->sprite.screen_x;
	h->sprite.end_x >= h->resol.w ? h->sprite.end_x = h->resol.w - 1 : 0;
}

void	sprite_draw_vertical_line(t_head *h)
{
	int d;

	d = h->sprite.start_y * 256 - h->resol.h * 128 + h->sprite.height * 128;
	h->sprite.tex_y = ((d * h->sprite.tex_h) / h->sprite.height) / 256;
	h->sprite.color = tex_to_pix_sprite(&h->sprite, h->sprite.tex_x,
		h->sprite.tex_y);
	if ((h->sprite.color & 0x00FFFFFF) != 0)
		my_pixel_put(h, h->sprite.start_x, h->sprite.start_y, h->sprite.color);
}

void	sprite_draw_line(t_head *h)
{
	h->sprite.tex_x = (int)(256 * (h->sprite.start_x - (-h->sprite.width / 2 +
		h->sprite.screen_x)) * h->sprite.tex_w / h->sprite.width) / 256;
	if (h->sprite.transform_y > 0 && h->sprite.start_x > 0 &&
		h->sprite.start_x < h->resol.w &&
		h->sprite.transform_y < h->ray.perp_buf[h->sprite.start_x])
	{
		h->sprite.start_y = -h->sprite.height / 2 + h->resol.h / 2;
		h->sprite.start_y < 0 ? h->sprite.start_y = 0 : 0;
		while (h->sprite.start_y < h->sprite.end_y)
		{
			sprite_draw_vertical_line(h);
			h->sprite.start_y++;
		}
	}
}
