/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:09:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/26 19:38:45 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall(t_head *h)
{
	int x;
	
	x = 0;

	while (x < h->resol.x)
	{
		h->ray.cam_y = 2 * x / (double)h->resol.x - 1; //в какой половине экрана (левая, середина, правая)
		
		h->ray.raydir_x = h->player.dir_x + h->ray.plane_x * h->ray.cam_y; //могут быть -1, 0, 1
		h->ray.raydir_y = h->player.dir_y + h->ray.plane_y * h->ray.cam_y;
		
		h->ray.map_x = (int)h->player.x; //задаем координаты квадратика map_xy (начала луча) такие же, как у игрока
		h->ray.map_y = (int)h->player.y;
		
		//если деление на ноль не работает
		// if (h->ray.raydir_y == 0)
		// 	h->ray.delta_x = 0;
		// else
		// {
		// 	h->ray.raydir_x == 0 ? h->ray.delta_x = 1 :
		// 		(h->ray.delta_x = fabs(1 / h->ray.raydir_x));
		// }
		// if (h->ray.raydir_x == 0)
		// 	h->ray.delta_y = 0;
		// else
		// {
		// 	h->ray.raydir_y == 0 ? h->ray.delta_y = 1 :
		// 		(h->ray.delta_y = fabs(1 / h->ray.raydir_y));
		// }
						
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
		//доходим лучом до стены
		while(h->map[h->ray.map_y][h->ray.map_x] != '1')
		{
			if(h->ray.first_side_x < h->ray.first_side_y)
			{
				h->ray.first_side_x += h->ray.delta_x;
				h->ray.map_x += h->ray.step_x;
				h->ray.side = 0;
			}
			else
			{
				h->ray.first_side_y += h->ray.delta_y;
				h->ray.map_y += h->ray.step_y;
				h->ray.side = 1;
			}
		}
		//рассчитываем расстояние, от плоскости игрока на экран (чтобы избежать фиш ай)
		if(h->ray.side == 0)
			h->ray.perp = (h->ray.map_x - h->player.x + (1 - h->ray.step_x) / 2) / h->ray.raydir_x;
		else
			h->ray.perp = (h->ray.map_y - h->player.y + (1 - h->ray.step_y) / 2) / h->ray.raydir_y;
		
		//задаем длину стенки
		h->wall.height = (int)(h->resol.y / h->ray.perp);

		//задем верхний и нижний пиксель
		h->wall.start = -h->wall.height / 2 + h->resol.y / 2;
		h->wall.start < 0 ? (h->wall.start = 0) : 0;
		h->wall.end = h->wall.height / 2 + h->resol.y / 2;
		h->wall.end >= h->resol.y ? (h->wall.end = h->resol.y - 1) : 0;
		
		h->wall.ceiling = 0;

		//где именно луч достиг стену по x
		if(h->ray.side == 0)
			h->wall.x = h->player.y + h->ray.perp * h->ray.raydir_y;
		else 
			h->wall.x = h->player.x + h->ray.perp * h->ray.raydir_x;
		h->wall.x -= floor(h->wall.x);
		
		//нужная х-координата текстуры
		h->wall.tex_x = (int)(h->wall.x * TEX_SIZE);
		if((h->ray.side == 0 && h->ray.raydir_x > 0) || (h->ray.side == 1 && h->ray.raydir_y < 0))
			h->wall.tex_x = TEX_SIZE - h->wall.tex_x - 1;

		//насколько увеличиваем координату текстуры на пиксель экрана
		h->wall.scale = 1.0 * TEX_SIZE / h->wall.height;

		//начальная координата текстуры
		h->wall.y = (h->wall.start - h->resol.y / 2 + h->wall.height / 2) * h->wall.scale;

		while(h->wall.ceiling <= h->wall.start)
		{
			my_pixel_put(h, x, h->wall.ceiling, h->color.ceiling_color);
			h->wall.ceiling++;
		}
		while(h->wall.start <= h->wall.end)
		{
			h->wall.tex_y = (int)h->wall.y & (TEX_SIZE - 1);
			h->wall.y += h->wall.scale;
			if(h->ray.side == 0 && h->player.x > h->ray.raydir_x + h->player.x)
				h->wall.color = tex_to_pix(&h->tex_n, h->wall.tex_x, h->wall.tex_y);

			if(h->ray.side == 1 && h->player.x < h->ray.raydir_x + h->player.x)
				h->wall.color = tex_to_pix(&h->tex_s, h->wall.tex_x, h->wall.tex_y);

			if(h->ray.side == 0 && h->player.y > h->ray.raydir_y + h->player.y)
				h->wall.color = tex_to_pix(&h->tex_w, h->wall.tex_x, h->wall.tex_y);

			if(h->ray.side == 1 && h->player.y < h->ray.raydir_y + h->player.y)
				h->wall.color = tex_to_pix(&h->tex_e, h->wall.tex_x, h->wall.tex_y);

			my_pixel_put(h, x, h->wall.start, h->wall.color);
			h->wall.start++;	
		}
		while(h->wall.end < h->resol.y)
		{
			my_pixel_put(h, x, h->wall.end, h->color.floor_color);
			h->wall.end++;
		}
		x++;
	}
}

void	render_all(t_head *h)
{
	int	max_x;
	int	max_y;

	h->mnlbx.mlx = mlx_init();
	h->mnlbx.mlx_win = mlx_new_window(h->mnlbx.mlx, h->resol.x, h->resol.y, "cub3D");
	h->data.img = mlx_new_image(h->mnlbx.mlx, h->resol.x, h->resol.y);
	h->data.addr = mlx_get_data_addr(h->data.img, &h->data.bpp, &h->data.line_length, &h->data.endian);

	parse_player(h);

	h->tex_n.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_n.path, &h->tex_n.x, &h->tex_n.y);
	h->tex_n.addr = mlx_get_data_addr(h->tex_n.img, &h->tex_n.bpp, &h->tex_n.line_length, &h->tex_n.endian);

	h->tex_s.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_s.path, &h->tex_s.x, &h->tex_s.y);
	h->tex_s.addr = mlx_get_data_addr(h->tex_s.img, &h->tex_s.bpp, &h->tex_s.line_length, &h->tex_s.endian);

	h->tex_w.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_w.path, &h->tex_w.x, &h->tex_w.y);
	h->tex_w.addr = mlx_get_data_addr(h->tex_w.img, &h->tex_w.bpp, &h->tex_w.line_length, &h->tex_w.endian);

	h->tex_e.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_e.path, &h->tex_e.x, &h->tex_e.y);
	h->tex_e.addr = mlx_get_data_addr(h->tex_e.img, &h->tex_e.bpp, &h->tex_e.line_length, &h->tex_e.endian);

	draw_wall(h);

	mlx_get_screen_size(h->mnlbx.mlx, &max_x, &max_y);

	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);

	mlx_hook(h->mnlbx.mlx_win, 2, 1L<<0, move, h);
	mlx_hook(h->mnlbx.mlx_win, 17, 0, x_close, 0);

	mlx_loop(h->mnlbx.mlx);
}