/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 19:15:42 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/07 17:01:37 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void parse_resolution(t_head *h, char *s)
{
	int	i;

	i = 2;
	while (s[i] == ' ')
		i++;
	if(s[i] >= '0' && s[i] <= '9')
		h->resol.w = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == ' ')
		while (s[i] == ' ')
			i++;
	else
		error_mssg(4);
	if (s[i] >= '0' && s[i] <= '9')
		h->resol.h = ft_atoi(s + i);
	while (s[i] >= '0' && s[i] <= '9')
		i++;	
	while (s[i] == ' ')
		i++;
	if(s[i] != '\0')
		error_mssg(4);
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}


void parse_colors(t_head *h, char *s, char c)
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
	if(s[i] != '\0')
		error_mssg(7);
}

int parse_textures(t_head *h, char *s, char side)
{
	int	i;
	int	fd;

	i = 3;
	while(s[i] == ' ')
		i++;
	side == 'N' ? h->tex_n.path = s + i : 0;
	side == 'S' ? h->tex_s.path = s + i : 0;
	side == 'W' ? h->tex_w.path = s + i : 0;
	side == 'E' ? h->tex_e.path = s + i : 0;
	if ((fd = open(s + i, O_RDONLY)) == -1)
		error_mssg(8);
	close(fd);
	
	
	return(0);
}

void	parse_sprite_tex(t_head *h, char *s)
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

void parse_player(t_head *h)
{
	int		j;
	int		i;

	h->player.x = 0;
	h->player.y = 0;

	j = h->start_map;
	while (h->map[j])
	{
		i = 0;
		while (h->map[j][i])
		{
			if (h->map[j][i] == 'N' || h->map[j][i] == 'S' || h->map[j][i] == 'W' || h->map[j][i] == 'E')
			{
				if (h->player.x && h->player.y)
					error_mssg(1);
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
	h->end_map = j - 1;
	if (!h->player.x && !h->player.y)
		error_mssg(1);
}
