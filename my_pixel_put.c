/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:55:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/27 13:44:01 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_head *h, int x, int y, int color)
{
	char	*dst;

	dst = h->data.addr + (y * h->data.line_length + x * (h->data.bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	tex_to_pix(t_texture *tex, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = tex->addr + (y * tex->line_length + (tex->x - x - 1) * (tex->bpp / 8));
	color = *(unsigned int*)dst;
	return(color);
}