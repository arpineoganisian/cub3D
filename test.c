// #include "cub3d.h"

// void	ft_swap_sprites(t_head *all, int i, int j)
// {
// 	t_sprite_buf	temp;

// 	temp = all->sprite.buf[i];
// 	all->sprite.buf[i] = all->sprite.buf[j];
// 	all->sprite.buf[j] = temp;
// }

// void	sort_sprites(t_head *all, int first, int last)
// {
// 	int			i;
// 	int			j;
// 	int			pin;

// 	if (first < last)
// 	{
// 		pin = first;
// 		i = first;
// 		j = last;
// 		while (i < j)
// 		{
// 			while (all->sprite.buf[i].dist <= all->sprite.buf[pin].dist && i < last)
// 				i++;
// 			while (all->sprite.buf[j].dist > all->sprite.buf[pin].dist)
// 				j--;
// 			if (i < j)
// 				ft_swap_sprites(all, i, j);
// 		}
// 		ft_swap_sprites(all, pin, j);
// 		sort_sprites(all, j + 1, last);
// 		sort_sprites(all, first, j - 1);
// 	}
// }