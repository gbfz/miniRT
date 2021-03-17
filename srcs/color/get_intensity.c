/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intensity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:35 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 18:30:03 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void		set_light_ray(double ray[3], double point[3],
								double light_coords[3])
{
	ray[0] = point[0] - light_coords[0];
	ray[1] = point[1] - light_coords[1];
	ray[2] = point[2] - light_coords[2];
	normalize(ray);
}

static void		invert_normal(double normal[3])
{
	normal[0] *= -1;
	normal[1] *= -1;
	normal[2] *= -1;
}

static double	get_n_dot_l(t_params *obj, double light_ray[3],
							double cam_ray[3])
{
	double normal_dot_light;
	double camera_dot_normal;

	camera_dot_normal = dot(cam_ray, obj->normal);
	if (camera_dot_normal >= 0)
		invert_normal(obj->normal);
	normal_dot_light = dot(obj->normal, light_ray) * -1;
	return (normal_dot_light);
}

double			get_intensity(t_light *light, t_params *obj,
								t_cam *cam, t_scene *scene)
{
	double	intensity;
	double	light_ray[3];
	double	normal_dot_light;

	if (light_has_obstacles(obj, light, cam->ray, scene) == 1)
		return (0);
	set_light_ray(light_ray, obj->point, light->coords);
	normal_dot_light = get_n_dot_l(obj, light_ray, cam->ray);
	if (normal_dot_light <= 0)
		return (0);
	intensity = light->intensity * normal_dot_light;
	return (intensity);
}
