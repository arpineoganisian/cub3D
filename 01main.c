/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:15:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/07 18:04:07 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_for_nl(char *str2)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (str2[i])
	{
		if (cnt < 8)
		{
			if (str2[i] != '\n' && str2[i + 1] == '\n')
				cnt++;
		}
		else if (str2[i] != '\n')
			if (str2[i + 1] == '\n' && str2[i + 2] == '\n')
				error_mssg(1);
		i++;
	}
}

int		check_arguments(int argc, char **argv, t_head *h)
{
	int	i;

	i = 0;
	h->save.flag = 0;
	if (argc == 2 || argc == 3)
	{
		while (ft_isprint(argv[1][i]))
			i++;
		if (ft_strncmp(".cub", argv[1] + (i - 4), 4))
			error_mssg(1);
	}
	if (argc == 3)
	{
		if (ft_strncmp("--save", argv[2], 7) == 0)
			h->save.flag = 1;
		else
			error_mssg(3);
	}
	if (argc != 2 && argc != 3)
		error_mssg(2);
	return (0);
}

void	parser(t_head *h)
{
	int j;

	j = 0;
	while (j < 8)
	{
		if (h->map[j][0] == 'R' && h->map[j][1] == ' ')
			parse_resolution(h, h->map[j]);
		if (h->map[j][0] == 'N' && h->map[j][1] == 'O' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == 'O' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'W' && h->map[j][1] == 'E' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'E' && h->map[j][1] == 'A' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == ' ')
			parse_sprite_tex(h, h->map[j]);
		if (h->map[j][0] == 'F' && h->map[j][1] == ' ')
			parse_colors(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'C' && h->map[j][1] == ' ')
			parse_colors(h, h->map[j], h->map[j][0]);
		j++;
	}
	h->start_map = j;
	map_valid(h);
}

// int		(int fd, char )
// {
	
// }

int		main(int argc, char **argv)
{
	int			fd;
	char		str[50];
	int			red;
	int			all;
	char		*str2;
	t_head		head;

	all = 0;
	check_arguments(argc, argv, &head);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_mssg(1);
	while ((red = read(fd, str, 50)))
		all += red;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (!(str2 = (char*)malloc(sizeof(char) * (all + 1))))
		error_mssg(6);
	read(fd, str2, all);
	str2[all] = '\0';
	check_map_for_nl(str2);
	if (!(head.map = ft_split(str2, '\n')))
		error_mssg(6);
	free(str2);
	close(fd);
	parser(&head);
}
