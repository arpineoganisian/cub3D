/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:50:23 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/06 21:41:02 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		max_strlen(char **map)
{
	int	max_len;
	int	j;

	max_len = 0;
	j = 0;
	while(map[j])
	{
		if ((int)ft_strlen(map[j]) > max_len)
			max_len = ft_strlen(map[j]);
		j++;
		
	}
	return(max_len);
}

char	**make_square(t_head *h)
{
	char	**map;
	int		i;
	int		j;
	int		len;
	
	i = 0;
	j = h->start_map;
	len = max_strlen(h->map + h->start_map) + 3;
	if (!(map = (char**)malloc(sizeof(char*) * (h->end_map - h->start_map + 3))))
		error_mssg(6);
	while (i <= h->end_map - h->start_map + 2)
	{
		if (!(map[i] = (char *)malloc(sizeof(char *) * len)))
			error_mssg(6);
		map[i][0] = ' ';
		i == 0 || i == h->end_map - h->start_map + 2 ? ft_memset(map[i], ' ', len - 1) : 
			ft_memcpy(&map[i][1], h->map[j], len - 1);
		map[i][len - 1] = ' ';
		map[i][len] = '\0';
		i != 0 ? j++ : 0;
 		i++;
	}
	map[i] = NULL;
	i = 0;
	return(map);
}

void	map_valid(t_head *h)
{
	int		j;
	int 	i;
	char	**m;
	
	j = 0;
	
	parse_player(h);
	m = make_square(h);
	while (m[j])
	{
		i = 0;
		while (m[j][i])
		{
			if (!(ft_strchr(" 012NSWE", m[j][i])))
				error_mssg(1);
			else 
			{
				if (m[j][i] == '0' || m[j][i] == '2')
				{
					if (m[j - 1][i - 1] == ' ' || m[j - 1][i] == ' ' || 
						m[j - 1][i + 1] == ' ' || m[j][i - 1] == ' ' || 
						m[j][i + 1] == ' ' || m[j + 1][i - 1] == ' ' || 
						m[j + 1][i] == ' ' || m[j + 1][i + 1] == ' ')
						error_mssg(1);
				}
			}
			i++;
			
		}
		j++;
	}
	// while() очистить карту
	// {
	// free(map);
		
	// }
	parse_sprite_pos(h);
	allocate_mem(h);
    render_all(h);
}