/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:09:41 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:54:26 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
