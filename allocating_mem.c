/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:26:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/05 20:26:05 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void allocate_mem(t_head *h)
{
	if (!(h->ray.perp_buf = (double*)malloc(sizeof(double) * h->resol.x)))
		error_mssg(6);
	
}