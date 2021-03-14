/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:27:36 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 16:19:36 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void		set_o_c(double o_c[3], t_sphere *sphere, double origin[3])
{
	o_c[0] = origin[0] - sphere->coords[0];
	o_c[1] = origin[1] - sphere->coords[1];
	o_c[2] = origin[2] - sphere->coords[2];
}

static double	min_pos(double a, double b)
{
	if (a > 0)
		if (b < 0 || a < b)
			return (a);
	if (b > 0)
		if (a < 0 || b < a)
			return (b);
	return (0);
}

static double	*get_normal(double *point, t_sphere *sphere)
{
	double *normal;

	normal = malloc(sizeof(double) * 3);
	if (normal == NULL)
		exit_error("Malloc failed");
	normal[0] = point[0] - sphere->coords[0];
	normal[1] = point[1] - sphere->coords[1];
	normal[2] = point[2] - sphere->coords[2];
	normalize(normal);
	return (normal);
}

static void		set_current_params(double point[3], t_sphere *sphere,
									t_params *current)
{
	current->id = 0;
	current->colors = sphere->colors;
	current->point = point;
	current->normal = get_normal(point, sphere);
}

double			intersect_sphere(void *obj, double ray[3],
								t_params *current, double origin[3])
{
	t_sphere	*sphere;
	double		eq[2];
	double		o_c[3];
	double		disc;
	double		t[3];

	sphere = (t_sphere *)obj;
	set_o_c(o_c, sphere, origin);
	eq[0] = dot(ray, o_c) * 2;
	eq[1] = dot(o_c, o_c) - pow(sphere->diameter / 2, 2);
	disc = eq[0] * eq[0] - 4 * eq[1];
	if (disc < 0)
		return (0);
	t[1] = (-eq[0] - sqrt(disc)) / 2;
	t[2] = (-eq[0] + sqrt(disc)) / 2;
	t[0] = min_pos(t[1], t[2]);
	if (t[0] == 0)
		return (0);
	if (current != NULL)
		set_current_params(get_point(origin, ray, t[0]), sphere, current);
	return (t[0]);
}
