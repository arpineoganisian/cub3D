/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08error_mssg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:41:31 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 20:34:39 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_mem(t_head *h)
{
	int i = 0;
	if (h->map)
	{
		while (h->map[i])
		{
			free(h->map[i]);
			i++;
		}
		free(h->map);
	}
	if (h->sprite.buf)
		free(h->sprite.buf);
	if (h->ray.perp_buf)
		free(h->ray.perp_buf);
	free(h);
}

int error_mssg(int err, t_head *h)
{
	err == 0 ? perror("Error") : 0;
	err == 1 ? write(1, "Error: Invalid map\n", 19) : 0;
	err == 2 ? write(1, "Error: Wrong number of arguments\n", 33) : 0;
	err == 3 ? write(1, "Error: Write '--save' for a screenshot\n", 39) : 0;
	err == 4 ? write(1, "Error: Please set valid display resolution\n", 43) : 0;
	err == 5 ? write(1, "Error: Failed to create a file\n", 31) : 0;
	err == 6 ? write(1, "Error: Failed to allocate memory\n", 33) : 0;
	err == 7 ? write(1, "Error: Please set valid floor/ceilling color\n", 45) : 0;
	err == 8 ? write(1, "Error: Failed to open a file\n", 29) : 0;
	err == 9 ? write(1, "Error: Wrong file extention of a texture\n", 41) : 0;
	err == 10 ? write(1, "Error: Please set all required elements\n", 40) : 0;
	err == 11 ? write(1, "Error: Wrong file extention of the texture\n", 43) : 0;
	err == 12 ? write(1, "Error: Please set one player on the map\n", 40) : 0;
	free_mem(h);
	exit(0);
}
