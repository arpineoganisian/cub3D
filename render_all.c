/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:09:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/21 18:45:47 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall(t_head *h)
{
	int x;
	
	x = 0;
	h->ray.plane_x = 0.66; //FOV
	h->ray.plane_y = 0; //FOV
	while (x < h->resol.x)
	{
		h->ray.map_x = (int)h->player.x; //задаем координаты квадратика map_xy (начала луча) такие же, как у игрока
		h->ray.map_y = (int)h->player.y;

		h->ray.cam_x = 2 * x / (double)h->resol.x - 1; //в какой половине экрана (левая, середина, правая)
		
		h->ray.raydir_x = h->player.dir_x + h->ray.plane_x * h->ray.cam_x; //могут быть -1, 0, 1
		h->ray.raydir_y = h->player.dir_y + h->ray.plane_y * h->ray.cam_x;
		
		h->ray.delta_x = fabs(1 / h->ray.raydir_x);
		h->ray.delta_y = fabs(1 / h->ray.raydir_y);

		//узнаем длину от начала луча до первого пересечения с целым x или у,
		//зная дельту и разницу между началом луча по х/у и целым х/у
		
		if(h->ray.raydir_x < 0)
		{
			h->ray.step_x = -1;
			h->ray.first_side_x = (h->player.x - h->ray.map_x) * h->ray.delta_x;
		}
		else
		{
			h->ray.step_x = 1;
			h->ray.first_side_x = (h->ray.map_x + 1.0 - h->player.x) * h->ray.delta_x;
		}
		if(h->ray.raydir_y < 0)
		{
			h->ray.step_y = -1;
			h->ray.first_side_y = (h->player.y - h->ray.map_y) * h->ray.delta_y;
		}
		else
		{
			h->ray.step_y = 1;
			h->ray.first_side_y = (h->ray.map_y + 1.0 - h->player.y) * h->ray.delta_y;
		}





		x++;
	}
}

void	render_all(t_head *h)
{
	h->mnlbx.mlx = mlx_init();
	h->mnlbx.mlx_win = mlx_new_window(h->mnlbx.mlx, h->resol.x, h->resol.y, "cub3D");
	h->data.img = mlx_new_image(h->mnlbx.mlx, h->resol.x, h->resol.y);
	h->data.addr = mlx_get_data_addr(h->data.img, &h->data.bpp, &h->data.line_length, &h->data.endian);

	parse_player(h);

	draw_wall(h);

	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);

	mlx_hook(h->mnlbx.mlx_win, 2, 1L<<0, move, h);
	mlx_hook(h->mnlbx.mlx_win, 17, 0, x_close, 0);

	mlx_loop(h->mnlbx.mlx);
}