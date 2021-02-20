/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:50:16 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:11:21 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_sprite_tex(t_head *h, char *s)
{
	int	i;
	int	fd;

	i = 0;
	while (s[i] == ' ')
		i++;
	h->sprite.path = s + i;
	i = 0;
	while (ft_isprint(h->sprite.path[i]))
		i++;
	if (ft_strncmp(".xpm", h->sprite.path + (i - 4), 4))
		error_mssg(9, h);
	if ((fd = open(h->sprite.path, O_RDONLY)) == -1)
		error_mssg(0, h);
}

void	count_sprites(t_head *h, int j, int i)
{
	h->sprite.num = 0;
	while (h->map[j])
	{
		i = 0;
		while (h->map[j][i])
		{
			if (h->map[j][i] == '2')
				h->sprite.num++;
			i++;
		}
		j++;
	}
}

void	parse_sprite_pos(t_head *h)
{
	int i;
	int j;
	int cnt;

	count_sprites(h, 8, 0);
	if (!(h->sprite.buf = (t_sprite_buf*)malloc(sizeof(t_sprite_buf) *
		h->sprite.num)))
		error_mssg(0, h);
	j = 8;
	cnt = 0;
	while (h->map[j])
	{
		i = 0;
		while (h->map[j][i])
		{
			if (h->map[j][i] == '2')
			{
				h->sprite.buf[cnt].x = i + 0.5;
				h->sprite.buf[cnt].y = j + 0.5;
				cnt++;
			}
			i++;
		}
		j++;
	}
}
