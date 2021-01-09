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

int parse_resolution(char *s, structure *h)
{
    int i;

    i = 2;
    while (s[i] == ' ')
        i++;
    if (s[i] >= '0' && s[i] <= '9')
        h->resol.rx = ft_atoi(s + i);
    while (s[i] >= '0' && s[i] <= '9')
        i++;
    while (s[i] == ' ')
        i++;
    if (s[i] >= '0' && s[i] <= '9')
        h->resol.ry = ft_atoi(s + i);
    while (s[i] >= '0' && s[i] <= '9')
        i++;
    while (s[i] == ' ')
        i++;
//    printf("x is %d, y is %d\n", h->resol.rwx, h->resol.rhy);
    if (s[i] == '\0')
        return (0);
    return (-1);
}

void parse(structure *h, char **str)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (str[j])
    {
        if (str[j][0] == 'R' && str[j][1] == ' ')
            if (parse_resolution(str[j], h))
                return ;
//        if (str[j][0] == 'N' && str[j][1] == 'O' && str[j][2] == ' ')
//        if (str[j][0] == 'S' && str[j][1] == 'O' && str[j][2] == ' ')
//        if (str[j][0] == 'W' && str[j][1] == 'E' && str[j][2] == ' ')
//        if (str[j][0] == 'E' && str[j][1] == 'A' && str[j][2] == ' ')
//        if (str[j][0] == 'S' && str[j][1] == ' ')
//        if (str[j][0] == 'F' && str[j][1] == ' ')
//        if (str[j][0] == 'C' && str[j][1] == ' ')
        if (str[j][0] == ' ' || str[j][0] == '0' || str[j][0] == '1')
        {
            print_map(str, j, h);
        }
        j++;
    }
}

int main(int argc, char **argv)
{
    int         fd;
    char        str[50];
    int         red;
    int         all;
    char        **splited;
    char        *str2;
    structure   head;

    all = 0;
    fd = open(argv[1], O_RDONLY);
    if (argc != 2)
        return (-1);
    while ((red = read(fd, str, 50)))
        all += red;
    close(fd);
    fd = open(argv[1], O_RDONLY);
    str2 = (char*)malloc(sizeof(char) * (all + 1));
    read(fd, str2, all);
    str2[all] = '\0';
    splited = ft_split(str2, '\n');
    free(str2);
    parse(&head, splited);
//    int i = 0;
//    while (splited[i])
//        printf("%s\n", splited[i++]);
}
