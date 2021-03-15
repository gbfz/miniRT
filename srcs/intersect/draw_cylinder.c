/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:40:51 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:55:27 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	*get_normal(double point[3], t_cylinder *cyl)
{
	double *normal;

	normal = malloc(sizeof(double) * 3);
	if (normal == NULL)
		exit_error("Malloc failed");
	normal[0] = point[0] - cyl->bottom_cap[0] - cyl->vector[0] * cyl->m;
	normal[1] = point[1] - cyl->bottom_cap[1] - cyl->vector[1] * cyl->m;
	normal[2] = point[2] - cyl->bottom_cap[2] - cyl->vector[2] * cyl->m;
	normalize(normal);
	return (normal);
}

static void		set_o_c(t_cylinder *cyl, double o_c[3], double origin[3])
{
	o_c[0] = origin[0] - cyl->bottom_cap[0];
	o_c[1] = origin[1] - cyl->bottom_cap[1];
	o_c[2] = origin[2] - cyl->bottom_cap[2];
}

static void		set_current_params(double point[3], t_cylinder *cyl,
									t_params *current)
{
	current->colors = cyl->colors;
	current->point = point;
	current->normal = get_normal(point, cyl);
}

static int		check_if_within_borders(double t, t_cylinder *cyl,
										double ray[3], double o_c[3])
{
	cyl->m = dot(ray, cyl->vector) * t + dot(o_c, cyl->vector);
	if (cyl->m >= 0 && cyl->m <= cyl->height)
		return (1);
	return (0);
}

double			intersect_cylinder(void *obj, double ray[3],
									t_params *current, double origin[3])
{
	t_cylinder	*cyl;
	double		o_c[3];
	double		eq[3];
	double		disc;
	double		t[3];

	cyl = (t_cylinder *)obj;
	set_o_c(cyl, o_c, origin);
	set_equation(eq, o_c, ray, cyl);
	disc = eq[1] * eq[1] - 4 * eq[0] * eq[2];
	if (disc < 0)
		return (0);
	t[1] = (-eq[1] - sqrt(disc)) / (2 * eq[0]);
	t[2] = (-eq[1] + sqrt(disc)) / (2 * eq[0]);
	if (t[1] >= 0 && check_if_within_borders(t[1], cyl, ray, o_c) == 1)
		t[0] = t[1];
	else if (t[2] >= 0 && check_if_within_borders(t[2], cyl, ray, o_c) == 1)
		t[0] = t[2];
	else
		return (0);
	if (current != NULL)
		set_current_params(get_point(origin, ray, t[0]), cyl, current);
	return (t[0]);
}
