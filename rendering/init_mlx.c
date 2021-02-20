/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:06:41 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 00:52:47 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	max_screen_size(t_head *h)
{
	int	max_w;
	int	max_h;

	mlx_get_screen_size(h->mnlbx.mlx, &max_w, &max_h);
	if (h->resol.w > max_w)
		h->resol.w = max_w;
	if (h->resol.h > max_h)
		h->resol.h = max_h;
}

void	init_mlx(t_head *h)
{
	h->mnlbx.mlx = mlx_init();
	h->mnlbx.mlx_win = mlx_new_window(h->mnlbx.mlx, h->resol.w, h->resol.h,
		"cub3D");
	h->data.img = mlx_new_image(h->mnlbx.mlx, h->resol.w, h->resol.h);
	h->data.addr = mlx_get_data_addr(h->data.img, &h->data.bpp,
		&h->data.line_length, &h->data.endian);
}

void	init_wall_textures(t_head *h)
{
	h->tex_n.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_n.path,
		&h->tex_n.w, &h->tex_n.h);
	h->tex_n.addr = mlx_get_data_addr(h->tex_n.img, &h->tex_n.bpp,
		&h->tex_n.line_length, &h->tex_n.endian);
	h->tex_s.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_s.path,
		&h->tex_s.w, &h->tex_s.h);
	h->tex_s.addr = mlx_get_data_addr(h->tex_s.img, &h->tex_s.bpp,
		&h->tex_s.line_length, &h->tex_s.endian);
	h->tex_w.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_w.path,
		&h->tex_w.w, &h->tex_w.h);
	h->tex_w.addr = mlx_get_data_addr(h->tex_w.img, &h->tex_w.bpp,
		&h->tex_w.line_length, &h->tex_w.endian);
	h->tex_e.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_e.path,
		&h->tex_e.w, &h->tex_e.h);
	h->tex_e.addr = mlx_get_data_addr(h->tex_e.img, &h->tex_e.bpp,
		&h->tex_e.line_length, &h->tex_e.endian);
}

void	init_sprite_texture(t_head *h)
{
	h->sprite.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->sprite.path,
		&h->sprite.tex_w, &h->sprite.tex_h);
	h->sprite.addr = mlx_get_data_addr(h->sprite.img, &h->sprite.bpp,
		&h->sprite.line_length, &h->sprite.endian);
}
