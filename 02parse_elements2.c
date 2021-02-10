/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02parse_elements2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 19:15:42 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 19:51:25 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	parse_sprite_tex(t_head *h, char *s)
{
	int	i;
	int	fd;

	i = 2;
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

void	parse_sprite_pos(t_head *h)
{
	int i;
	int j;
	int cnt;
	h->sprite.num = 0;
	j = h->start_map;
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
	if (!(h->sprite.buf = (t_sprite_buf*)malloc(sizeof(t_sprite_buf) * h->sprite.num)))
		error_mssg(0, h);
	j = h->start_map;
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

int		create_rgb(int r, int g, int b, t_head *h)
{
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		error_mssg(7, h);
	return(r << 16 | g << 8 | b);
}

void	parse_colors(t_head *h, char *s, char c)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		r = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		g = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		b = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	c == 'F' ? (h->color.floor_color = create_rgb(r, g, b, h)) :
		(h->color.ceiling_color = create_rgb(r, g, b, h));
	if (s[i] != '\0')
		error_mssg(7, h);
}
