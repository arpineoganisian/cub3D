/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:50:23 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/11 22:34:30 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		max_strlen(char **map)
{
	int	max_len;
	int	j;

	max_len = 0;
	j = 0;
	while (map[j])
	{
		if ((int)ft_strlen(map[j]) > max_len)
			max_len = ft_strlen(map[j]);
		j++;
	}
	return (max_len);
}

char	**make_square(t_head *h, int j)
{
	char	**map;
	int		i;
	int		len;
	int		str_num;

	i = -1;
	len = max_strlen(h->map + j) + 3;
	str_num = h->end_map - j + 3;
	if (!(map = (char**)malloc(sizeof(char*) * (str_num + 1))))
		error_mssg(0, h);
	while (++i < str_num)
	{
		if (!(map[i] = (char *)malloc(sizeof(char *) * len)))
			error_mssg(0, h);
		map[i][0] = ' ';
		ft_memset(map[i], ' ', len - 1);
		i != 0 && i != str_num - 1 ?
			ft_memcpy(&map[i][1], h->map[j], ft_strlen(h->map[j])) : 0;
		map[i][len - 1] = ' ';
		map[i][len] = '\0';
		i != 0 ? j++ : 0;
	}
	map[i] = NULL;
	return (map);
}

void	check_spaces(char **map, int j, int i, t_head *h)
{
	if (map[j - 1][i - 1] == ' ' || map[j - 1][i] == ' ' ||
		map[j - 1][i + 1] == ' ' || map[j][i - 1] == ' ' ||
		map[j][i + 1] == ' ' || map[j + 1][i - 1] == ' ' ||
		map[j + 1][i] == ' ' || map[j + 1][i + 1] == ' ')
		error_mssg(1, h);
}

void	free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	map_valid(t_head *h)
{
	int		j;
	int		i;
	char	**map;

	j = 0;
	parse_player(h);
	map = make_square(h, 8);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (!(ft_strchr(" 012NSWE", map[j][i])))
				error_mssg(1, h);
			if ((ft_strchr("02NSWE", map[j][i])))
				check_spaces(map, j, i, h);
			i++;
		}
		j++;
	}
	free_map(map);
	parse_sprite_pos(h);
	render_all(h);
}
