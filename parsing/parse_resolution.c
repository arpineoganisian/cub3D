/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:08:59 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 20:15:12 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(t_head *h, char *s)
{
	int	i;

	i = 2;
	while (s[i] == ' ')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		h->resol.w = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == ' ')
		while (s[i] == ' ')
			i++;
	else
		error_mssg(4, h);
	if (s[i] >= '0' && s[i] <= '9')
		h->resol.h = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] != '\0')
		error_mssg(4, h);
	if (h->resol.h <= 0 || h->resol.w <= 0)
		error_mssg(4, h);
	if (!(h->ray.perp_buf = (double*)malloc(sizeof(double) * h->resol.w)))
		error_mssg(6, h);
}
