/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01init_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:15:56 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 19:24:14 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_zero(t_head *h)
{
	h->map = NULL;
	h->tmp_str = NULL;
	h->sprite.buf = NULL;
	h->ray.perp_buf = NULL;
	h->r = 0;
	h->s = 0; 
	h->so = 0;
	h->no = 0;
	h->we = 0;
	h->ea = 0;
	h->f = 0;
	h->c = 0;
}