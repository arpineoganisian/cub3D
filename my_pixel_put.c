/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:55:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/26 13:44:17 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_head *h, int x, int y, int color)
{
	char	*dst;

	dst = h->data.addr + (y * h->data.line_length + x * (h->data.bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	tex_to_pix(t_head *h, int x, int y)
{
	int				*dst;
	unsigned int	color;

	dst = h->tex_n.addr + (y * h->tex_n.line_length + x * (h->tex_n.bpp / 8));
	color = *(unsigned int*)dst;
	return(color);
}