/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:15:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:08:51 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_all_elements(t_head *h)
{
	if (h->so != 1 || h->no != 1 || h->we != 1 || h->ea != 1 || h->c != 1 ||
		h->f != 1)
		error_mssg(10, h);
	map_valid(h);
}

void	parser(t_head *h, int j)
{
	while (j < 8 && h->map[j])
	{
		if (h->map[j][0] == 'R' && h->map[j][1] == ' ' && ++h->r)
			parse_resolution(h, h->map[j]);
		if (h->map[j][0] == 'N' && h->map[j][1] == 'O' && h->map[j][2] == ' ' &&
			++h->no)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == 'O' && h->map[j][2] == ' ' &&
			++h->so)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'W' && h->map[j][1] == 'E' && h->map[j][2] == ' ' &&
			++h->we)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'E' && h->map[j][1] == 'A' && h->map[j][2] == ' ' &&
			++h->ea)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == ' ' && ++h->s)
			parse_sprite_tex(h, h->map[j] + 2);
		if (h->map[j][0] == 'F' && h->map[j][1] == ' ' && ++h->f)
			parse_colors(h, h->map[j] + 2, h->map[j][0]);
		if (h->map[j][0] == 'C' && h->map[j][1] == ' ' && ++h->c)
			parse_colors(h, h->map[j] + 2, h->map[j][0]);
		j++;
	}
	check_all_elements(h);
}
