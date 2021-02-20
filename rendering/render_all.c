/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:06:35 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 20:14:50 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_head *h)
{
	int x;

	x = -1;
	while (++x < h->resol.w)
	{
		h->ray.map_x = (int)h->player.x;
		h->ray.map_y = (int)h->player.y;
		ray_dir_and_delta(h, x);
		first_side_ray_meet(h);
		ray_hit(h);
		fish_eye(h);
		wall_params(h);
		x_coord_of_hit(h);
		choose_texture(h);
		texture_calculations(h);
		wall_draw_line(h, x);
		h->ray.perp_buf[x] = h->ray.perp;
	}
}

void	draw_sprites(t_head *h)
{
	int i;

	i = 0;
	calculate_dist_to_sprites(h, 0);
	sort_sprites(h, 0, h->sprite.num - 1);
	while (i < h->sprite.num)
	{
		h->sprite.current_x = h->sprite.buf[i].x - h->player.x;
		h->sprite.current_y = h->sprite.buf[i].y - h->player.y;
		sprite_initial_calculations(h);
		vertical_line(h);
		horizontal_line(h);
		while (h->sprite.start_x < h->sprite.end_x)
		{
			sprite_draw_line(h);
			h->sprite.start_x++;
		}
		i++;
	}
}

void	render_all(t_head *h)
{
	max_screen_size(h);
	init_mlx(h);
	init_wall_textures(h);
	init_sprite_texture(h);
	draw_wall(h);
	draw_sprites(h);
	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);
	if (!h->save.flag)
	{
		mlx_hook(h->mnlbx.mlx_win, 2, 1L << 0, key_press, h);
		mlx_hook(h->mnlbx.mlx_win, 3, 1L << 0, key_release, h);
		mlx_hook(h->mnlbx.mlx_win, 17, 0, x_close, h);
		mlx_loop_hook(h->mnlbx.mlx, move, h);
		mlx_loop(h->mnlbx.mlx);
	}
	else
		screenshot(h);
}
