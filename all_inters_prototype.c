/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inters_prototype.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:20:14 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:39:39 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

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
		current_t = scene->intersect[lst->id](lst->obj, ray, &current_params, cam->coords);
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
		if (get_nearest_intersection(scene, cam->ray, &params, cam) != NO_INTERSECTION)
		{
			color = get_color(&params, scene, cam);
			pixel_put(img, pixel, color);
		}
		free(cam->ray);
	}
}

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img_lst	*img_lst;
	t_img_lst	*lst_start;
	t_img		img;
}				t_data;

static int		display_next_image(int key, t_data *data)
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
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.ll, &data->img.en);
	draw_scene(scene, &data->img, cam);
	img_lstadd_back(&data->img_lst, img_lstnew(data->img));
}

int				main(int ac, char **av)
{
	t_data		data;
	t_scene		*scene;
	int			config;

	if (check_file(ac, av[1]) == -1)
		return (1);
	config = open(av[1], O_RDONLY);
	if (config == -1)
		return (1);
	scene = parser(config);
	close(config);
	if (scene == NULL)
		return (1);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, scene->res->x, scene->res->y, "holy shit");
	data.img_lst = NULL;
	while (scene->cam)
	{
		draw_image(&data, scene, scene->res, scene->cam);
		free_cam(scene->cam);
		scene->cam = scene->cam->next;
	}
	data.lst_start = data.img_lst;
	while (data.img_lst)
	{
		mlx_put_image_to_window(data.mlx, data.win, data.img_lst->img.img, 0, 0);
		mlx_hook(data.win, 2, 1l << 0, &display_next_image, &data);
		//mlx_hook(data.win, 2, 1l << 0, &simple_exit, NULL);
		mlx_loop(data.mlx);
	}
	return (0);
}

/*
int				main(int ac, char **av)
{
	void			*mlx;
	void			*win;
	t_img_lst		*img_lst;
	t_img			img;
	t_scene			*scene;
	int				config;

	if (check_file(ac, av[1]) == -1)
		return (1);
	config = open(av[1], O_RDONLY);
	if (config == -1)
		return (1);
	scene = parser(config);
	close(config);
	if (scene == NULL)
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, scene->res.x, scene->res.y, "holy shit");
	while (scene->cam)
	{
		img.img = mlx_new_image(mlx, scene->res.x, scene->res.y);
		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.en);
		draw_scene(scene, &img, scene->cam);
		scene->cam = scene->cam->next;
		img_lstadd_back(&img_lst, img_lstnew(img));
	}
	while (img_lst)
	{
		mlx_hook(win, 2, 1L << 0, &display_next_image, &img_lst);
		printf("%p\n", img_lst->img);
		//mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, win);
		//mlx_clear_window(mlx, win);
		mlx_put_image_to_window(mlx, win, img_lst->img.img, 0, 0);
		mlx_loop(mlx);
	}
	return (0);
}
*/

/*
int				main(int ac, char **av)
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		*scene;
	int			config;

	//printf("falloff = %f\n", FOG * (1 - DENS));
	if (check_file(ac, av[1]) == -1)
		return (1);
	config = open(av[1], O_RDONLY);
	scene = parser(config);
	close(config);
	if (scene == NULL)
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, scene->res.x, scene->res.y, "wow");
	img.img = mlx_new_image(mlx, scene->res.x, scene->res.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.en);
	draw_scene(scene, &img, scene->cam);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
*/
