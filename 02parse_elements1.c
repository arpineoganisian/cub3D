/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02parse_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:50:16 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 19:50:00 by hwoodwri         ###   ########.fr       */
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
	j = h->start_map - 1;
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
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0')
		error_mssg(4, h);
	if (h->resol.h <= 0 || h->resol.w <= 0)
		error_mssg(4, h);
}

void	parse_textures(t_head *h, char *s, char side)
{
	int	i;
	int	fd;
	int path_start;

	i = 0;
	while (s[i] == ' ')
		i++;
	path_start = i;
	while (ft_isprint(s[i]))
		i++;
	if (ft_strncmp(".xpm", s + (i - 4), 4))
		error_mssg(9, h);
	if ((fd = open(s + path_start, O_RDONLY)) == -1)
		error_mssg(0, h);
	side == 'N' ? h->tex_n.path = s + path_start : 0;
	side == 'S' ? h->tex_s.path = s + path_start : 0;
	side == 'W' ? h->tex_w.path = s + path_start : 0;
	side == 'E' ? h->tex_e.path = s + path_start : 0;
	close(fd);
}
