/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:15:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/18 17:44:59 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_resolution(t_struct *h, char *s)
{
	int	i;

	i = 2;
	while (s[i] == ' ')
		i++;
	if(s[i] >= '0' && s[i] <= '9')
		h->resol.rx = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		h->resol.ry = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if(s[i] == '\0')
		return (0);
	return (-1);
}

void parse_player(t_struct *h)
{
	int j;
	int i;

	j = h->start_map;
	while (h->s[j])
	{
		i = 0;
		while (h->s[j][i])
		{
			if (h->s[j][i] == 'N' || h->s[j][i] == 'S' || h->s[j][i] == 'W' || h->s[j][i] == 'E')
			{
				h->player.px = i;
				h->player.py = j - h->start_map;
				if (h->s[j][i] == 'N')
					h->player.dir = M_PI_2;
				if (h->s[j][i] == 'W')
					h->player.dir = M_PI;
				if (h->s[j][i] == 'S')
					h->player.dir = 3 * M_PI_2;
				if (h->s[j][i] == 'E')
					h->player.dir = 0;
			}
			i++;
		}
		j++;
	}
}

void parse(t_struct *h)
{
	int j;

	j = 0;

	while(h->s[j])
	{
		if (h->s[j][0] == 'R' && h->s[j][1] == ' ')
			if (parse_resolution(h, h->s[j]))
				return ;
        //        if (h->s[j][0] == 'N' && h->s[j][1] == 'O' && h->s[j][2] == ' ')
        //        if (h->s[j][0] == 'S' && h->s[j][1] == 'O' && h->s[j][2] == ' ')
        //        if (h->s[j][0] == 'W' && h->s[j][1] == 'E' && h->s[j][2] == ' ')
        //        if (h->s[j][0] == 'E' && h->s[j][1] == 'A' && h->s[j][2] == ' ')
        //        if (h->s[j][0] == 'S' && h->s[j][1] == ' ')
        //        if (h->s[j][0] == 'F' && h->s[j][1] == ' ')
        //        if (h->s[j][0] == 'C' && h->s[j][1] == ' ')
		if (h->s[j][0] == ' ' || h->s[j][0] == '0' || h->s[j][0] == '1')
        {
			h->start_map = j;
            print_all(h);
        }
        j++;
    }
}

int main(int argc, char **argv)
{
    int			fd;
    char		str[50];
    int			red;
    int			all;
    char		*str2;
    t_struct	head;

    all = 0;

    if (argc != 2)
        return (-1);
    fd = open(argv[1], O_RDONLY);
    while ((red = read(fd, str, 50)))
        all += red;
    close(fd);
    fd = open(argv[1], O_RDONLY);
    str2 = (char*)malloc(sizeof(char) * (all + 1));
    read(fd, str2, all);
    str2[all] = '\0';
    head.s = ft_split(str2, '\n');
    free(str2);
    close(fd);
    parse(&head);
}
