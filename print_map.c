#include "cub3d.h"

void print_square(structure *h, int i, int j)
{
    int x1;
    int y1;

    h->map.x = j * 5;
    h->map.y = i * 5;

    x1 = h->map.y + 5;
    y1 = h->map.x + 5;
    while (h->map.y < y1)
    {
        //обновить x
        while (h->map.x < x1)
        {
            mlx_pixel_put(h->mnlbx.mlx, h->mnlbx.mlx_win, h->map.x, h->map.y, 0xFFFFFF);
            h->map.x++;
        }    
        h->map.y++;
    }
}

void print_map(char **s, int j, structure *h)
{
    h->map.x = 0;
    h->map.y = 0;
    h->mnlbx.mlx = mlx_init();
    h->mnlbx.mlx_win = mlx_new_window(h->mnlbx.mlx, h->resol.rx, h->resol.ry, "cub3D");

    while (s[j])
    {
        int i;

        i = 0;
        while (s[j][i])
        {
            if (s[j][i] == '1')
                print_square(h, i, j);
            i++;
        }
        j++;
    }
    mlx_loop(h->mnlbx.mlx);
}