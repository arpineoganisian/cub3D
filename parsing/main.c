/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 21:57:30 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:27:43 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_zeros(t_head *h)
{
	h->map = NULL;
	h->tmp_str = NULL;
	h->sprite.buf = NULL;
	h->ray.perp_buf = NULL;
	h->r = 0;
	h->s = 0;
	h->so = 0;
	h->no = 0;
	h->we = 0;
	h->ea = 0;
	h->f = 0;
	h->c = 0;
	h->key.w = 0;
	h->key.s = 0;
	h->key.a = 0;
	h->key.d = 0;
	h->key.left = 0;
	h->key.right = 0;
	h->key.esc = 0;
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

int		main(int argc, char **argv)
{
	int			fd;
	char		str[50];
	int			all;
	t_head		*head;

	if (!(head = (t_head*)malloc(sizeof(t_head))))
		error_mssg(0, head);
	init_zeros(head);
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
	parser(head, 0);
}
