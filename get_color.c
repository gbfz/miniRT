/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:55:13 by meldora           #+#    #+#             */
/*   Updated: 2021/03/10 16:21:10 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

static void		invert_normal(double normal[3])
{
	normal[0] *= -1;
	normal[1] *= -1;
	normal[2] *= -1;
}

static void		set_shadow_ray(double light_ray[3], t_params *obj,
									double light_coords[3], double cam_ray[3])
{
	double sign;

	sign = 1;
	if (dot(obj->normal, cam_ray) <= 0)
		sign = -1;
	light_ray[0] = (obj->point[0] - obj->normal[0] * 0.00000005 * sign) - light_coords[0];
	light_ray[1] = (obj->point[1] - obj->normal[1] * 0.00000005 * sign) - light_coords[1];
	light_ray[2] = (obj->point[2] - obj->normal[2] * 0.00000005 * sign) - light_coords[2];
	normalize(light_ray);
}

static double	get_distance(double a[3], double b[3])
{
	double distance;

	distance = pow(b[0] - a[0], 2);
	distance += pow(b[1] - a[1], 2);
	distance += pow(b[2] - a[2], 2);
	return (sqrt(distance));
}

static int		light_has_obstacles(t_params *obj, t_light *light, double cam_ray[3], t_scene *scene)
{
	t_obj	*lst;
	double	light_ray[3];
	double	current_t;
	double	nearest_t;

	lst = scene->obj_lst;
	set_shadow_ray(light_ray, obj, light->coords, cam_ray);
	current_t = get_distance(obj->point, light->coords);
	while (lst)
	{
		nearest_t = scene->intersect[lst->id](lst->obj, light_ray, NULL, light->coords);
		if (nearest_t < current_t && nearest_t > 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void		set_light_ray(double ray[3], double point[3], double light_coords[3])
{
	ray[0] = point[0] - light_coords[0];
	ray[1] = point[1] - light_coords[1];
	ray[2] = point[2] - light_coords[2];
	normalize(ray);
}

static double	get_n_dot_l(t_params *obj, double light_ray[3], double cam_ray[3])
{
	double normal_dot_light;
	double camera_dot_normal;

	camera_dot_normal = dot(cam_ray, obj->normal);
	if (camera_dot_normal >= 0)
		invert_normal(obj->normal);
	normal_dot_light = dot(obj->normal, light_ray) * -1;
	return (normal_dot_light);
}

static double	get_intensity(t_light *light, t_params *obj, t_cam *cam, t_scene *scene)
{
	double	intensity;
	double	light_ray[3];
	double	normal_dot_light;
	double	distance;
	double	falloff;

	if (light_has_obstacles(obj, light, cam->ray, scene) == 1)
		return (0);
	set_light_ray(light_ray, obj->point, light->coords);
	normal_dot_light = get_n_dot_l(obj, light_ray, cam->ray);
	if (normal_dot_light <= 0)
		return (0);
	distance = get_distance(obj->point, light->coords);
	falloff = FOG  * (1 - DENS) / pow(distance, 2);
	intensity = light->intensity * falloff * normal_dot_light;
	return (intensity);
}

static double	*get_coeff_light(t_light *light, t_params *obj, t_cam *cam, t_scene *scene)
{
	double	*coeff_light;
	double	local_intensity;

	coeff_light = ft_calloc(sizeof(double), 3);
	while (light)
	{
		local_intensity = get_intensity(light, obj, cam, scene);
		coeff_light[0] += local_intensity * light->colors[0] / 255;
		coeff_light[1] += local_intensity * light->colors[1] / 255;
		coeff_light[2] += local_intensity * light->colors[2] / 255;
		light = light->next;
	}
	free(obj->point);
	free(obj->normal);
	return (coeff_light);	
}

int				get_color(t_params *obj, t_scene *scene, t_cam *cam)
{
	int		color;
	double	coeff_amb[3];
	double	*coeff_light;

	coeff_amb[0] = scene->amb->ratio * scene->amb->colors[0] / 255;
	coeff_amb[1] = scene->amb->ratio * scene->amb->colors[1] / 255;
	coeff_amb[2] = scene->amb->ratio * scene->amb->colors[2] / 255;
	coeff_light = get_coeff_light(scene->light, obj, cam, scene);
	;
	color = 0;
	color |= ((int)min(obj->colors[0] * (coeff_amb[0] + coeff_light[0]), 255)) << 16;
	color |= ((int)min(obj->colors[1] * (coeff_amb[1] + coeff_light[1]), 255)) << 8;
	color |= ((int)min(obj->colors[2] * (coeff_amb[2] + coeff_light[2]), 255));
	;
	free(coeff_light);
	return (color);
}