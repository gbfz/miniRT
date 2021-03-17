/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:53:11 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 12:18:47 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#include <stdio.h>

static void		set_file_header(t_img *img, t_res *res,
								int padding_size, int fd)
{
	unsigned char	header[14];
	int				file_size;

	ft_bzero(header, 14);
	(void)padding_size;
	file_size = 54 + (img->bpp / 8 * res->x) * res->y;
	header[0] = 'B';
	header[1] = 'M';
	header[2] = file_size;
	header[3] = (file_size >> 8);
	header[4] = (file_size >> 16);
	header[5] = (file_size >> 24);
	header[10] = 54;
	if (!write(fd, header, 14))
		exit_error("Couldn't write to .bmp file header");
}

static void		set_info_header(t_img *img, t_res *res, int fd)
{
	unsigned char	header[40];

	ft_bzero(header, 40);
	header[0] = 40;
	header[4] = res->x;
	header[5] = (res->x >> 8);
	header[6] = (res->x >> 16);
	header[7] = (res->x >> 24);
	header[8] = res->y;
	header[9] = (res->y >> 8);
	header[10] = (res->y >> 16);
	header[11] = (res->y >> 24);
	header[12] = 1;
	header[14] = img->bpp;
	if (!write(fd, header, 40))
		exit_error("Couldn't write to .bmp info header");
}

static void		write_bmp(t_img *img, t_res *res, int fd)
{
	int h;
	int w;

	h = res->y;
	while (h--)
	{
		w = 0;
		while (w < res->x)
		{
			if (!write(fd, img->addr + (h * img->ll + w * img->bpp / 8), 4))
				exit_error("Couldn't write to .bmp file");
			w++;
		}
	}
}

static void		create_bmp(t_img *img, t_res *res)
{
	int		fd;

	fd = open("miniRT.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_error("Couldn't create .bmp file");
	set_file_header(img, res, 0, fd);
	set_info_header(img, res, fd);
	write_bmp(img, res, fd);
	close(fd);
	ft_putstr_fd("Created .bmp file\n", 1);
}

void			render_screenshot(t_data *data, t_scene *scene)
{
	draw_image(data, scene, scene->res, scene->cam);
	create_bmp(&data->img, scene->res);
}
