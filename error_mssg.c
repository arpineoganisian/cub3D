/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mssg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:41:31 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/04 14:13:12 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int error_mssg(int err)
{
	err == 1 ? write(1, "Invalid map file\n", 12) : 0;
	err == 2 ? write(1, "Wrong number of arguments\n", 26) : 0;
	err == 3 ? write(1, "Write ''--save'' if you want to take a screenshot\n", 50) : 0;
	err == 4 ? write(1, "Please set valid display resolution\n", 36) : 0;
	err == 5 ? write(1, "Failed to create a file\n", 24) : 0;
	
	return(0);
}