/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shadows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:43:05 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 19:47:19 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void		set_shadow_ray(double light_ray[3], t_params *obj,
									double light_coords[3], double cam_ray[3])
{
	double sign;

	sign = 1;
	if (dot(obj->normal, cam_ray) <= 0)
		sign = -1;
	light_ray[0] = (obj->point[0] - obj->normal[0] * 0.0000005 * sign)
					- light_coords[0];
	light_ray[1] = (obj->point[1] - obj->normal[1] * 0.0000005 * sign)
					- light_coords[1];
	light_ray[2] = (obj->point[2] - obj->normal[2] * 0.0000005 * sign)
					- light_coords[2];
	normalize(light_ray);
}

int				light_has_obstacles(t_params *obj, t_light *light,
									double cam_ray[3], t_scene *scene)
{
	t_obj	*lst;
	double	shadow_ray[3];
	double	current_t;
	double	nearest_t;

	lst = scene->obj_lst;
	set_shadow_ray(shadow_ray, obj, light->coords, cam_ray);
	current_t = get_distance(obj->point, light->coords);
	while (lst)
	{
		nearest_t = scene->intersect[lst->id](lst->obj, shadow_ray,
												NULL, light->coords);
		if (nearest_t < current_t && nearest_t > 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}