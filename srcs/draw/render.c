/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:28:12 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:43:12 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

static void		draw_scene(t_scene *scene, t_img *img, t_cam *cam)
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

void			draw_image(t_data *data, t_scene *scene, t_res *res, t_cam *cam)
{
	data->img.img = mlx_new_image(data->mlx, res->x, res->y);
	data->img.addr = mlx_get_data_addr(data->img.img,
								&data->img.bpp, &data->img.ll, &data->img.en);
	draw_scene(scene, &data->img, cam);
	img_lstadd_back(&data->img_lst, img_lstnew(data->img));
}
