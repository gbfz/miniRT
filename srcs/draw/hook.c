/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:30:39 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 19:31:13 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int		key_hook(int key, t_data *data)
{
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		data->img_lst = data->img_lst->next;
		if (data->img_lst == NULL)
			data->img_lst = data->lst_start;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_lst->img.img, 0, 0);
	return (0);
}

int		exit_hook(int button, int x, int y, t_data *data)
{
	exit(0);
}