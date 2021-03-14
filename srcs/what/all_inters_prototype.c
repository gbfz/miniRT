/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inters_prototype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:20:14 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 17:25:27 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			pixel_put(t_img *img, int pixel[2], int color)
{
	char	*dst;

	dst = img->addr + (pixel[Y] * img->ll + pixel[X] * img->bpp / 8);
	*(unsigned int *)dst = color;
}

static void		set_nearest_params(t_params *nearest, t_params current)
{
	nearest->colors = current.colors;
	if (nearest->point != NULL)
		free(nearest->point);
	if (nearest->normal != NULL)
		free(nearest->normal);
	nearest->point = current.point;
	nearest->normal = current.normal;
}

static void		cast_ray(double **ray, t_res *res, t_cam *cam, int pixel[2])
{
	*ray = malloc(sizeof(double) * 3);
	if (*ray == NULL)
		exit_error("Malloc failed");
	(*ray)[0] = pixel[X] - res->x / 2;
	(*ray)[1] = res->y / 2 - pixel[Y];
	(*ray)[2] = res->x / (2 * tan(cam->fov / 2));
	normalize(*ray);
	multiply_by_matrix(*ray, cam->matrix);
}

static void		null_params(t_params *n, t_params *c)
{
	n->point = NULL;
	c->point = NULL;
	n->normal = NULL;
	c->normal = NULL;
}

static void		free_current_params(t_params *current)
{
	free(current->point);
	current->point = NULL;
	free(current->normal);
	current->normal = NULL;
}

static double	get_nearest_intersection(t_scene *scene, double *ray,
										t_params *nearest_params, t_cam *cam)
{
	t_obj		*lst;
	double		current_t;
	double		nearest_t;
	t_params	current_params;

	lst = scene->obj_lst;
	nearest_t = NO_INTERSECTION;
	null_params(nearest_params, &current_params);
	while (lst)
	{
		current_t = scene->intersect[lst->id](lst->obj, ray,
												&current_params, cam->coords);
		if (current_t < nearest_t && current_t > 0)
		{
			nearest_t = current_t;
			set_nearest_params(nearest_params, current_params);
		}
		else if (current_t != 0)
			free_current_params(&current_params);
		lst = lst->next;
	}
	return (nearest_t);
}

static int		switch_to_next_pixel(int pixel[2], t_res *res)
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

static void		set_first_pixel(int pixel[2])
{
	pixel[X] = -1;
	pixel[Y] = 0;
}

void			draw_scene(t_scene *scene, t_img *img, t_cam *cam)
{
	int			pixel[2];
	t_params	params;
	int			color;

	set_first_pixel(pixel);
	while (switch_to_next_pixel(pixel, scene->res) != 0)
	{
		cast_ray(&cam->ray, scene->res, scene->cam, pixel);
		if (get_nearest_intersection(scene, cam->ray, &params, cam)
			!= NO_INTERSECTION)
		{
			color = get_color(&params, scene, cam);
			pixel_put(img, pixel, color);
		}
		free(cam->ray);
	}
}

static int		key_hook(int key, t_data *data)
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

static int		simple_exit(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

static void		free_cam(t_cam *cam)
{
	free(cam->coords);
	free(cam->vector);
	free_matrix(cam->matrix);
	free(cam);
}

static void		draw_image(t_data *data, t_scene *scene, t_res *res, t_cam *cam)
{
	data->img.img = mlx_new_image(data->mlx, res->x, res->y);
	data->img.addr = mlx_get_data_addr(data->img.img,
								&data->img.bpp, &data->img.ll, &data->img.en);
	draw_scene(scene, &data->img, cam);
	img_lstadd_back(&data->img_lst, img_lstnew(data->img));
}

static int		exit_hook(int button, int x, int y, t_data *data)
{
	exit(0);
}

static void		display_scenes(t_data *data)
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

static void		draw_scenes(t_data *data, t_scene *scene)
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

static void		init_data(t_data *data, t_scene *scene)
{
	data->mlx = mlx_init();
	manage_resolution(data, scene);
	data->win = mlx_new_window(data->mlx, scene->res->x,
								scene->res->y, "miniRT");
	data->img_lst = NULL;
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
	draw_scenes(&data, scene);
	display_scenes(&data);
	return (0);
}
