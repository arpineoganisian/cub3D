/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 17:58:50 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/01/03 17:58:51 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd;
    char    str[50];
    int     red;
    int     all;
    char    **splited;
    char    *str2;

    all = 0;
    fd = open(argv[1], O_RDONLY);
    (void)argc;
    while ((red = read(fd, str, 50)))
        all += red;
    close(fd);
    fd = open(argv[1], O_RDONLY);
    str2 = (char*)malloc(sizeof(char) * (all + 1));
    read(fd, str2, all);
    str2[all] = '\0';
    splited = ft_split(str2, '\n');
    
//    int i = 0;
//    while (splited[i])
//        printf("%s\n", splited[i++]);
}
