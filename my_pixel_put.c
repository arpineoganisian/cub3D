/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:55:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/16 13:09:06 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_struct *h, int x, int y, int color)
{
	char	*dst;

	dst = h->data.addr + (y * h->data.line_length + x * (h->data.bpp / 8));
	*(unsigned int*)dst = color;
}
