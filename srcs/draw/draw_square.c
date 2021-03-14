/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:12:59 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 18:37:42 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	get_orient(double p[3], double p1[3], double p2[3], double *n)
{
	double o;
	double *c;
	double v1[3];
	double v2[3];

	v1[0] = p1[0] - p[0];
	v1[1] = p1[1] - p[1];
	v1[2] = p1[2] - p[2];
	;
	v2[0] = p2[0] - p[0];
	v2[1] = p2[1] - p[1];
	v2[2] = p2[2] - p[2];
	;
	c = cross(v1, v2);
	o = dot(c, n);
	free(c);
	return (o);
}

static void		set_current_params(double point[3],
									t_square *sq, t_params *current)
{
	current->id = 2;
	current->colors = sq->colors;
	current->point = point;
	current->normal = malloc(sizeof(double) * 3);
	if (current->normal == NULL)
		exit_error("Malloc failed");
	ft_memcpy(current->normal, sq->vector, sizeof(double) * 3);
}

static double	no_inter_free(double **p)
{
	free(*p);
	*p = NULL;
	return (0);
}

static void		set_c_o(double c_o[3], double coords[3], double origin[3])
{
	c_o[0] = coords[0] - origin[0];
	c_o[1] = coords[1] - origin[1];
	c_o[2] = coords[2] - origin[2];
}

static int		check_if_within_borders(double point[3], t_square *sq)
{
	if (get_orient(point, sq->vertices[0], sq->vertices[1], sq->vector) >= 0)
		return (no_inter_free(&point));
	if (get_orient(point, sq->vertices[1], sq->vertices[2], sq->vector) >= 0)
		return (no_inter_free(&point));
	if (get_orient(point, sq->vertices[2], sq->vertices[3], sq->vector) >= 0)
		return (no_inter_free(&point));
	if (get_orient(point, sq->vertices[3], sq->vertices[0], sq->vector) >= 0)
		return (no_inter_free(&point));
	return (1);
}

double			intersect_square(void *obj, double ray[3],
								t_params *current, double origin[3])
{
	t_square	*sq;
	double		dot_n_ray;
	double		t;
	double		*point;
	double		c_o[3];

	sq = (t_square *)obj;
	dot_n_ray = dot(sq->vector, ray);
	if (fabs(dot_n_ray) < 0.000001)
		return (0);
	set_c_o(c_o, sq->coords, origin);
	t = dot(c_o, sq->vector) / dot_n_ray;
	if (t < 0)
		return (0);
	point = get_point(origin, ray, t);
	if (check_if_within_borders(point, sq) == 0)
		return (0);
	if (current != NULL)
		set_current_params(point, sq, current);
	else
		free(point);
	return (t);
}
