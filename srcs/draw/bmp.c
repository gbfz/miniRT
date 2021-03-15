/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:53:11 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:11:24 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static void		set_file_header(t_img *img, t_res *res, int padding_size, int fd)
{
	unsigned char	header[14];
	int				file_size;

	ft_bzero(header, 14);
	file_size = 54 + (img->bpp / 8 * res->x + padding_size) * res->y;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
	if (!write(fd, header, 14))
		exit_error("Error while writing bmp header");
}

static void		set_info_header(t_img *img, t_res *res, int fd)
{
	unsigned char	header[40];

	ft_bzero(header, 40);
	header[0] = (unsigned char)40;
	header[4] = (unsigned char)(res->x);
	header[5] = (unsigned char)(res->x >> 8);
	header[6] = (unsigned char)(res->x >> 16);
	header[7] = (unsigned char)(res->x >> 24);
	header[8] = (unsigned char)(res->y);
	header[9] = (unsigned char)(res->y >> 8);
	header[10] = (unsigned char)(res->y >> 16);
	header[11] = (unsigned char)(res->y >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(img->bpp);
	if (!write(fd, header, 40))
		exit_error("Error while writing bmp header");
}

static void		create_bmp(t_img *img, t_res *res)
{
	int				line;
	int				fd;
	int				padding_size;
	unsigned char	padding[3];

	line = res->y;
	ft_bzero(padding, 3);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit_error("Couldn't create .bmp file");
	padding_size = (4 - (res->x * img->bpp / 8) % 4) % 4;
	set_file_header(img, res, padding_size, fd);
	set_info_header(img, res, fd);
	while (line >= 0)
	{
		if (!write(fd, img->addr + (line * res->x * img->bpp / 8), img->ll))
			exit_error("Couldn't write to .bmp file");
		if (!write(fd, padding, padding_size))
			exit_error("Couldn't write to .bmp file");
		line--;
	}
	close(fd);
}

void			render_screenshot(t_data *data, t_scene *scene)
{
	draw_image(data, scene, scene->res, scene->cam);
	create_bmp(&data->img, scene->res);
}