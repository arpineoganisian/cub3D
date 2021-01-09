#include "cub3d.h"

int main()
{
    void    *mlx;
    void    *mlx_win;
    int     x;
    int     y;

    x = 100;
    y = 100;
 
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello!");
    while (y++ < 400)
    {
        x = 100;
        while (x++ < 400)
            mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
    }
    mlx_loop(mlx);
}