/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:55:04 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/02 19:55:06 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h> // open
# include <unistd.h> // read, close

#include <stdio.h> // УДАЛИТЬ

typedef struct  struct_mnlbx
{
    void    *mlx;
    void    *mlx_win;
}               sMnlbx;

typedef struct  struct_resolution
{
    int rx;
    int ry;
}               sResolution;

//структура для 2д карты
typedef struct  struct_map
{
    int x;
    int y;
}               sMap;

typedef struct  s_struct
{
    sMnlbx      mnlbx;
    sResolution resol;
    sMap        map;

}               structure;

int main(int argc, char **argv);
void print_map(char **s, int j, structure *h);

#endif