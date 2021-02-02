/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:15:00 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/31 19:42:57 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_resolution(t_head *h, char *s)
{
	int	i;

	i = 2;
	while (s[i] == ' ')
		i++;
	if(s[i] >= '0' && s[i] <= '9')
		h->resol.x = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		h->resol.y = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if(s[i] == '\0')
		return (0);
	return (-1);
}

void parse_player(t_head *h)
{
	int j;
	int i;

	j = h->start_map;
	while (h->map[j])
	{
		i = 0;
		while (h->map[j][i])
		{
			if (h->map[j][i] == 'N' || h->map[j][i] == 'S' || h->map[j][i] == 'W' || h->map[j][i] == 'E')
			{
				h->player.x = i + 0.5;
				h->player.y = j + 0.5;
				if (h->map[j][i] == 'N')
				{
					h->player.dir_x = 0;
					h->player.dir_y = -1;
					h->ray.plane_x = 0.66; //FOV
					h->ray.plane_y = 0; //FOV
				}
				if (h->map[j][i] == 'E')
				{
					h->player.dir_x = 1;
					h->player.dir_y = 0;
					h->ray.plane_x = 0; //FOV
					h->ray.plane_y = 0.66; //FOV
				}
				if (h->map[j][i] == 'S')
				{
					h->player.dir_x = 0;
					h->player.dir_y = 1;
					h->ray.plane_x = -0.66; //FOV
					h->ray.plane_y = 0; //FOV
				}
				if (h->map[j][i] == 'W')
				{
					h->player.dir_x = -1;
					h->player.dir_y = 0;
					h->ray.plane_x = 0; //FOV
					h->ray.plane_y = -0.66; //FOV
				}
			}
			i++;
		}
		j++;
	}
}


int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

int parse_colors(t_head *h, char *s, char c)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 2;
	while (s[i] == ' ')
		i++;
	if(s[i] >= '0' && s[i] <= '9')
		r = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if(s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		g = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if(s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		b = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	c == 'F' ? (h->color.floor_color = create_rgb(r, g, b)) :
		(h->color.ceiling_color = create_rgb(r, g, b));
	if(s[i] == '\0')
		return (0);
	return (-1);
}

int parse_textures(t_head *h, char *s, char side)
{
	int	i;

	i = 3;
	while(s[i] == ' ')
		i++;
	side == 'N' ? h->tex_n.path = s + i : 0;
	side == 'S' ? h->tex_s.path = s + i : 0;
	side == 'W' ? h->tex_w.path = s + i : 0;
	side == 'E' ? h->tex_e.path = s + i : 0;
	
	//if()
	return(0);
}

void	parse_sprite(t_head *h, char *s)
{
	int	i;

	i = 2;
	while (s[i] == ' ')
		i++;
	h->sprite.path = s + i;

}

void parse_sprite_pos(t_head *h)
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

	// if (!(h->sprite.x = (double*)malloc(sizeof(double) * (h->sprite.num - 1))))
	// 	return ;
	// if (!(h->sprite.y = (double*)malloc(sizeof(double) * (h->sprite.num - 1))))
	// 	return ;
	// if (!(h->sprite.order = (int*)malloc(sizeof(int) * (h->sprite.num - 1))))
	// 	return ;
	// if (!(h->sprite.dist = (double*)malloc(sizeof(double) * (h->sprite.num - 1))))
	// 	return ;

	if (!(h->sprite.buf = (t_sprite_buf*)malloc(sizeof(t_sprite_buf) * h->sprite.num)))
		return ;

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

void parse(t_head *h)
{
	int j;

	j = 0;
	while(h->map[j])
	{
		if (h->map[j][0] == 'R' && h->map[j][1] == ' ')
			if (parse_resolution(h, h->map[j]))
				return ;
        if (h->map[j][0] == 'N' && h->map[j][1] == 'O' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == 'O' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
        if (h->map[j][0] == 'W' && h->map[j][1] == 'E' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
        if (h->map[j][0] == 'E' && h->map[j][1] == 'A' && h->map[j][2] == ' ')
			parse_textures(h, h->map[j], h->map[j][0]);
		if (h->map[j][0] == 'S' && h->map[j][1] == ' ')
			parse_sprite(h, h->map[j]);
		if (h->map[j][0] == 'F' && h->map[j][1] == ' ')
			if (parse_colors(h, h->map[j], h->map[j][0]))
				return ;
        if (h->map[j][0] == 'C' && h->map[j][1] == ' ')
			if (parse_colors(h, h->map[j], h->map[j][0]))
				return ;
		if (h->map[j][0] == ' ' || h->map[j][0] == '0' || h->map[j][0] == '1')
        {
			h->start_map = j;
			parse_sprite_pos(h);
			parse_player(h);
            render_all(h);
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
    t_head		head;

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
    head.map = ft_split(str2, '\n');
    free(str2);
    close(fd);
    parse(&head);
}
