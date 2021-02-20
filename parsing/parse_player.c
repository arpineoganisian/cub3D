/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:11:07 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:44:05 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_pos_params(t_head *h, char c)
{
	c == 'N' || c == 'S' ? h->ray.plane_y = 0 :
		(h->ray.plane_x = 0);
	c == 'N' || c == 'S' ? h->player.dir_x = 0 :
		(h->player.dir_y = 0);
	if (c == 'N')
	{
		h->player.dir_y = -1;
		h->ray.plane_x = 0.66;
	}
	if (c == 'E')
	{
		h->player.dir_x = 1;
		h->ray.plane_y = 0.66;
	}
	if (c == 'S')
	{
		h->player.dir_y = 1;
		h->ray.plane_x = -0.66;
	}
	if (c == 'W')
	{
		h->player.dir_x = -1;
		h->ray.plane_y = -0.66;
	}
}

void	parse_player(t_head *h)
{
	int		j;
	int		i;

	h->player.x = 0;
	h->player.y = 0;
	j = 7;
	while (h->map[++j])
	{
		i = -1;
		while (h->map[j][++i])
		{
			if (h->map[j][i] == 'N' || h->map[j][i] == 'S' ||
				h->map[j][i] == 'W' || h->map[j][i] == 'E')
			{
				if (h->player.x && h->player.y)
					error_mssg(12, h);
				h->player.x = i + 0.5;
				h->player.y = j + 0.5;
				player_pos_params(h, h->map[j][i]);
			}
		}
	}
	h->end_map = j - 1;
	if (!h->player.x && !h->player.y)
		error_mssg(12, h);
}
