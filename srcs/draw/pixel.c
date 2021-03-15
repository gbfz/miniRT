/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:21:58 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:43:07 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	pixel_put(t_img *img, int pixel[2], int color)
{
	char	*dst;

	dst = img->addr + (pixel[Y] * img->ll + pixel[X] * img->bpp / 8);
	*(unsigned int *)dst = color;
}

int		switch_to_next_pixel(int pixel[2], t_res *res)
{
	pixel[X] += 1;
	if (pixel[X] == res->x)
	{
		pixel[X] = 0;
		pixel[Y] += 1;
	}
	if (pixel[Y] == res->y)
		return (0);
	return (1);
}

void	set_first_pixel(int pixel[2])
{
	pixel[X] = -1;
	pixel[Y] = 0;
}
