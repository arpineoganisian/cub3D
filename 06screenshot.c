/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06screenshot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <hwoodwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:49:14 by hwoodwri          #+#    #+#             */
/*   Updated: 2021/02/10 19:01:24 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void screenshot(t_head *h)
{
	unsigned char	bmp_file_header[14];
	unsigned char	bmp_info_header[40];
	int				bf_size;
	int				height;
	int				line_length;
	
	if ((h->save.fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655)) == -1) // 0655 - права, чтобы пересоздавать файл
		error_mssg(5, h);
	
	bf_size = 14 + 40 + (4 * h->resol.w * h->resol.h);
	
	ft_bzero(bmp_file_header, 14);
	ft_bzero(bmp_info_header, 40);
	
	bmp_file_header[0] = (unsigned char)'B';
	bmp_file_header[1] = (unsigned char)'M';
	bmp_file_header[2] = (unsigned int)(bf_size);
	bmp_file_header[3] = (unsigned int)(bf_size >> 8);
	bmp_file_header[4] = (unsigned int)(bf_size >> 16);
	bmp_file_header[5] = (unsigned int)(bf_size >> 24);
	bmp_file_header[10] = (unsigned int)54;
	
	bmp_info_header[0] = (unsigned int)40;
	bmp_info_header[4] = (unsigned int)(h->resol.w);
	bmp_info_header[5] = (unsigned int)(h->resol.w >> 8);
	bmp_info_header[6] = (unsigned int)(h->resol.w >> 16);
	bmp_info_header[7] = (unsigned int)(h->resol.w >> 24);
	bmp_info_header[8] = (unsigned int)(h->resol.h);
	bmp_info_header[9] = (unsigned int)(h->resol.h >> 8);
	bmp_info_header[10] = (unsigned int)(h->resol.h >> 16);
	bmp_info_header[11] = (unsigned int)(h->resol.h >> 24);
	bmp_info_header[12] = (unsigned int)1;
	bmp_info_header[14] = (unsigned int)32;
	
	height = h->resol.h;
	line_length = h->resol.w * h->data.bpp / 8;
	write(h->save.fd, bmp_file_header, 14);
	write(h->save.fd, bmp_info_header, 40);
	while(height >= 0)
	{
		write(h->save.fd, (unsigned char*)(h->data.addr + height * h->data.line_length), line_length);
		height--;
	}
	close(h->save.fd);
}
