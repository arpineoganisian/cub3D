/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 01:09:46 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/03 00:15:18 by hwoodwri         ###   ########.fr       */
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
		h->wall.end >= h->resol.y || h->wall.end < 0 ? (h->wall.end = h->resol.y - 1) : 0;
		
		h->wall.ceiling = 0;

		//где именно луч достиг стену по x
		if(h->ray.side == 0)
			h->wall.x = h->player.y + h->ray.perp * h->ray.raydir_y;
		else 
			h->wall.x = h->player.x + h->ray.perp * h->ray.raydir_x;
		h->wall.x -= floor(h->wall.x);

		//выбираю структуру в зависимости от стены
		if(h->ray.side == 0 && h->player.x > h->ray.raydir_x + h->player.x)
			h->current_tex = h->tex_w;

		if(h->ray.side == 0 && h->player.x < h->ray.raydir_x + h->player.x)
			h->current_tex = h->tex_e;

		if(h->ray.side == 1 && h->player.y > h->ray.raydir_y + h->player.y)
			h->current_tex = h->tex_n;

		if(h->ray.side == 1 && h->player.y < h->ray.raydir_y + h->player.y)
			h->current_tex = h->tex_s;

		//нужная х-координата текстуры
		h->wall.tex_x = (int)(h->wall.x * h->current_tex.x);
		if((h->ray.side == 0 && h->ray.raydir_x > 0) || (h->ray.side == 1 && h->ray.raydir_y < 0))
			h->wall.tex_x = h->current_tex.x - h->wall.tex_x - 1;

		//насколько увеличиваем координату текстуры на пиксель экрана
		h->wall.scale = 1.0 * h->current_tex.y / h->wall.height;

		//начальная координата текстуры
		h->wall.y = (h->wall.start - h->resol.y / 2 + h->wall.height / 2) * h->wall.scale;

		while(h->wall.ceiling <= h->wall.start)
		{
			my_pixel_put(h, x, h->wall.ceiling, h->color.ceiling_color);
			h->wall.ceiling++;
		}
		while(h->wall.start <= h->wall.end)
		{
			h->wall.tex_y = (int)h->wall.y & (h->current_tex.x - 1);
			h->wall.y += h->wall.scale;

			h->wall.color = tex_to_pix(&h->current_tex, h->wall.tex_x, h->wall.tex_y);

			my_pixel_put(h, x, h->wall.start, h->wall.color);
			h->wall.start++;	
		}
		while(h->wall.end < h->resol.y)
		{
			my_pixel_put(h, x, h->wall.end, h->color.floor_color);
			h->wall.end++;
		}
		h->ray.perp_buf[x] = h->ray.perp;
		x++;
	}
}

void sort_sprites(t_head *h,t_sprite_buf *buf, double left, double right)
{
	int				l_hold; //левая граница
	int				r_hold; // правая граница
	t_sprite_buf 	tmp;
	
	l_hold = left;
	r_hold = right;
	tmp = buf[(int)left]; //
	while (left < right) // пока границы не сомкнутся
  	{
		while ((buf[(int)right].dist <= tmp.dist) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			buf[(int)left] = buf[(int)right]; 
			left++; // сдвигаем левую границу вправо
		}
		while ((buf[(int)left].dist >= tmp.dist) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			buf[(int)right] = buf[(int)left]; 
			right--; // сдвигаем правую границу вправо
		}
	}
	buf[(int)left] = tmp;
	tmp.dist = left;
	left = l_hold;
	right = r_hold;
	if (left < tmp.dist) // Рекурсивно вызываем сортировку для левой и правой части массива
		sort_sprites(h, buf, left, tmp.dist - 1);
	if (right > tmp.dist)
		sort_sprites(h, buf, tmp.dist + 1, right);
}

void draw_sprites(t_head *h)
{
	int i;
	int d;

	i = 0;
	while(i < h->sprite.num)
	{
		h->sprite.buf[i].dist = (h->player.x - h->sprite.buf[i].x) * (h->player.x - h->sprite.buf[i].x) + (h->player.y - h->sprite.buf[i].y) * (h->player.y - h->sprite.buf[i].y);
		i++;
	}

	//!сортировка (нулевой спрайт - самый дальний, рисуем его первым)
	sort_sprites(h, h->sprite.buf, 0, h->sprite.num - 1);

	i = 0;
	while(i < h->sprite.num)
	{
		//переводим положение камеры в положение относительно игрока
		h->sprite.current_x = h->sprite.buf[i].x - h->player.x;
		h->sprite.current_y = h->sprite.buf[i].y - h->player.y;

		h->sprite.inv = 1.0 / (h->ray.plane_x * h->player.dir_y - h->player.dir_x * h->ray.plane_y);

		h->sprite.transform_x = h->sprite.inv * (h->player.dir_y * h->sprite.current_x - h->player.dir_x * h->sprite.current_y);
		h->sprite.transform_y = h->sprite.inv * (-h->ray.plane_y * h->sprite.current_x + h->ray.plane_x * h->sprite.current_y);
		
		h->sprite.screen_x = (int)(h->resol.x / 2 * (1 + h->sprite.transform_x / h->sprite.transform_y));
	
	//по вертикали
		h->sprite.height = abs((int)(h->resol.y / h->sprite.transform_y)); //используем transform вместо реального расстояния от фишай эффекта
		h->sprite.start_y = -h->sprite.height / 2 + h->resol.y / 2;
		h->sprite.start_y < 0 ? h->sprite.start_y = 0 : 0;
		h->sprite.end_y = h->sprite.height / 2 + h->resol.y / 2;
		h->sprite.end_y >= h->resol.y ? h->sprite.end_y = h->resol.y - 1 : 0;

	// по горизонтали
		h->sprite.width = abs((int)(h->resol.y / h->sprite.transform_y)); 
		h->sprite.start_x = -h->sprite.width / 2 + h->sprite.screen_x;
		h->sprite.start_x < 0 ? h->sprite.start_x = 0 : 0;
		h->sprite.end_x = h->sprite.width / 2 + h->sprite.screen_x;
		h->sprite.end_x >= h->resol.x ? h->sprite.end_x = h->resol.x - 1 : 0;

		
		while(h->sprite.start_x < h->sprite.end_x)
		{
			h->sprite.tex_x = (int)(256 * (h->sprite.start_x - (-h->sprite.width / 2 + h->sprite.screen_x)) * h->sprite.tex_w / h->sprite.width) / 256;
			if(h->sprite.transform_y > 0 && h->sprite.start_x > 0 && h->sprite.start_x < h->resol.x && h->sprite.transform_y < h->ray.perp_buf[h->sprite.start_x])
			{
				h->sprite.start_y = -h->sprite.height / 2 + h->resol.y / 2;				
				while(h->sprite.start_y < h->sprite.end_y)
				{
					d = h->sprite.start_y * 256 - h->resol.y * 128 + h->sprite.height * 128;
					h->sprite.tex_y = ((d * h->sprite.tex_h) / h->sprite.height) / 256;
					h->sprite.color = tex_to_pix_sprite(&h->sprite, h->sprite.tex_x, h->sprite.tex_y);
					if((h->sprite.color & 0x00FFFFFF) != 0)
						my_pixel_put(h, h->sprite.start_x, h->sprite.start_y, h->sprite.color);
					h->sprite.start_y++;
				}
			}
			h->sprite.start_x++;
		}
		i++;
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

	h->tex_n.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_n.path, &h->tex_n.x, &h->tex_n.y);
	h->tex_n.addr = mlx_get_data_addr(h->tex_n.img, &h->tex_n.bpp, &h->tex_n.line_length, &h->tex_n.endian);

	h->tex_s.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_s.path, &h->tex_s.x, &h->tex_s.y);
	h->tex_s.addr = mlx_get_data_addr(h->tex_s.img, &h->tex_s.bpp, &h->tex_s.line_length, &h->tex_s.endian);

	h->tex_w.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_w.path, &h->tex_w.x, &h->tex_w.y);
	h->tex_w.addr = mlx_get_data_addr(h->tex_w.img, &h->tex_w.bpp, &h->tex_w.line_length, &h->tex_w.endian);

	h->tex_e.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->tex_e.path, &h->tex_e.x, &h->tex_e.y);
	h->tex_e.addr = mlx_get_data_addr(h->tex_e.img, &h->tex_e.bpp, &h->tex_e.line_length, &h->tex_e.endian);

	//спрайт
	h->sprite.img = mlx_xpm_file_to_image(h->mnlbx.mlx, h->sprite.path, &h->sprite.tex_w, &h->sprite.tex_h);
	h->sprite.addr = mlx_get_data_addr(h->sprite.img, &h->sprite.bpp, &h->sprite.line_length, &h->sprite.endian);
	
	draw_wall(h);
	draw_sprites(h);

	mlx_get_screen_size(h->mnlbx.mlx, &max_x, &max_y);

	mlx_put_image_to_window(h->mnlbx.mlx, h->mnlbx.mlx_win, h->data.img, 0, 0);

	mlx_hook(h->mnlbx.mlx_win, 2, 1L<<0, move, h);
	mlx_hook(h->mnlbx.mlx_win, 17, 0, x_close, 0);

	mlx_loop(h->mnlbx.mlx);
}