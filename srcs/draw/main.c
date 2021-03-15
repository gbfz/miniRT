/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:34:06 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:10:09 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

static void		render(t_data *data, t_scene *scene)
{
	while (scene->cam)
	{
		draw_image(data, scene, scene->res, scene->cam);
		free_cam(scene->cam);
		scene->cam = scene->cam->next;
	}
}

int				main(int ac, char **av)
{
	t_data		data;
	t_scene		*scene;
	int			config;

	check_file(ac, av);
	config = open(av[1], O_RDONLY);
	if (config == -1)
		exit_error("Failed to open .rt file");
	scene = parser(config);
	init_data(&data, scene);
	if (ac == 3)
	{
		render_screenshot(&data, scene);
		return (0);
	}
	render(&data, scene);
	display(&data);
	return (0);
}
