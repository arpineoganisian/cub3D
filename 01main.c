/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:15:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 20:36:28 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			error_mssg(11, h);
	}
	if (argc == 3)
	{
		if (ft_strncmp("--save", argv[2], 7) == 0)
			h->save.flag = 1;
		else
			error_mssg(3, h);
	}
	if (argc != 2 && argc != 3)
		error_mssg(2, h);
	return (0);
}

int		count_symbols(int fd, char *str, t_head *h)
{
	int	all;
	int	red;

	all = 0;
	while ((red = read(fd, str, 50)) > 0)
		all += red;
	if (red == -1)
		error_mssg(0, h);
	return (all);
}

void	check_map_for_nl(char *str2, t_head *h)
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
				error_mssg(1, h);
		i++;
	}
}

void	parser(t_head *h)
{
	int j;

	j = 0;
	while (j < 8 && h->map[j])
	{
		if (h->map[j][0] == 'R' && h->map[j][1] == ' ' && ++h->r)
			parse_resolution(h, h->map[j]);
		if (h->map[j][0] == 'N' && h->map[j][1] == 'O' && h->map[j][2] == ' ' && ++h->no)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == 'O' && h->map[j][2] == ' ' && ++h->so)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'W' && h->map[j][1] == 'E' && h->map[j][2] == ' ' && ++h->we)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'E' && h->map[j][1] == 'A' && h->map[j][2] == ' ' && ++h->ea)
			parse_textures(h, h->map[j] + 3, h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == ' ' && ++h->s)
			parse_sprite_tex(h, h->map[j]);
		if (h->map[j][0] == 'F' && h->map[j][1] == ' ' && ++h->f)
			parse_colors(h, h->map[j] + 2, h->map[j][0]);
		if (h->map[j][0] == 'C' && h->map[j][1] == ' ' && ++h->c)
			parse_colors(h, h->map[j] + 2, h->map[j][0]);
		j++;
	}
	h->start_map = j;
	if (h->so != 1 || h->no != 1 || h->we != 1 || h->ea != 1 ||h->c != 1 || h->f != 1)
	 	error_mssg(10, h);
	map_valid(h);
}

int		main(int argc, char **argv)
{
	int			fd;
	char		str[50];
	int			all;
	t_head		*head;

	if(!(head = (t_head*)malloc(sizeof(t_head))))
		error_mssg(0, head);
	init_zero(head);
	check_arguments(argc, argv, head);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_mssg(0, head);
	all = count_symbols(fd, str, head);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (!(head->tmp_str = (char*)malloc(sizeof(char) * (all + 1))))
		error_mssg(0, head);
	read(fd, head->tmp_str, all);
	head->tmp_str[all] = '\0';
	check_map_for_nl(head->tmp_str, head);
	if (!(head->map = ft_split(head->tmp_str, '\n')))
		error_mssg(0, head);
	free(head->tmp_str);
	close(fd);
	parser(head);
}