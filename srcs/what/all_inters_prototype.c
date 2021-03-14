/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inters_prototype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:20:14 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 19:34:41 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			display(t_data *data)
{
	data->lst_start = data->img_lst;
	while (data->img_lst)
	{
		mlx_put_image_to_window(data->mlx, data->win,
								data->img_lst->img.img, 0, 0);
		mlx_hook(data->win, 2, 1l << 0, &key_hook, data);
		mlx_hook(data->win, 17, 1l << 0, &exit_hook, data);
		mlx_loop(data->mlx);
	}
}

static void		free_cam(t_cam *cam)
{
	free(cam->coords);
	free(cam->vector);
	free_matrix(cam->matrix);
	free(cam);
}

void			render(t_data *data, t_scene *scene)
{
	while (scene->cam)
	{
		draw_image(data, scene, scene->res, scene->cam);
		free_cam(scene->cam);
		scene->cam = scene->cam->next;
	}
}

static void		manage_resolution(t_data *data, t_scene *scene)
{
	int	max_screen_width;
	int	max_screen_height;

	mlx_get_screen_size(data->mlx, &max_screen_width, &max_screen_height);
	if (scene->res->x > max_screen_width)
		scene->res->x = max_screen_width;
	if (scene->res->y > max_screen_height)
		scene->res->y = max_screen_height;
}

void			init_data(t_data *data, t_scene *scene)
{
	data->mlx = mlx_init();
	manage_resolution(data, scene);
	data->win = mlx_new_window(data->mlx, scene->res->x,
								scene->res->y, "miniRT");
	data->img_lst = NULL;
}
