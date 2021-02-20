/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 19:15:42 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/12 19:09:52 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_digits(char *s, int i)
{
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (i);
}

int		create_rgb(int r, int g, int b, t_head *h)
{
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		error_mssg(7, h);
	return (r << 16 | g << 8 | b);
}

void	parse_colors(t_head *h, char *s, char c)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		r = ft_atoi(s + i);
	i = skip_digits(s, i);
	if (s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		g = ft_atoi(s + i);
	i = skip_digits(s, i);
	if (s[i] == ',')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		b = ft_atoi(s + i);
	i = skip_digits(s, i);
	c == 'F' ? (h->color.floor_color = create_rgb(r, g, b, h)) :
		(h->color.ceiling_color = create_rgb(r, g, b, h));
	if (s[i] != '\0')
		error_mssg(7, h);
}
