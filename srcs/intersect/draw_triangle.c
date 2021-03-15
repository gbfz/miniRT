/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:26:27 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:13:50 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	*get_edge(double a[3], double b[3])
{
	double *edge;

	edge = malloc(sizeof(double) * 3);
	if (edge == NULL)
		exit_error("Malloc failed");
	edge[0] = a[0] - b[0];
	edge[1] = a[1] - b[1];
	edge[2] = a[2] - b[2];
	return (edge);
}

static double	*get_t_vec(double origin[3], double vertex[3])
{
	double *tvec;

	tvec = malloc(sizeof(double) * 3);
	if (tvec == NULL)
		exit_error("Malloc failed");
	tvec[0] = origin[0] - vertex[0];
	tvec[1] = origin[1] - vertex[1];
	tvec[2] = origin[2] - vertex[2];
	return (tvec);
}

static double	check_barycentric_coords(double origin[3], double vertex[3],
											double ray[3], double *edge[2])
{
	double	det;
	double	*v[3];
	double	c[3];

	set_vectors_to_null(v);
	v[PVEC] = cross(ray, edge[1]);
	det = dot(edge[0], v[PVEC]);
	if (fabs(det) < 0.00001)
		return (free_vectors(v));
	det = 1 / det;
	;
	v[TVEC] = get_t_vec(origin, vertex);
	c[U] = dot(v[TVEC], v[PVEC]) * det;
	if (c[U] < 0 || c[U] > 1)
		return (free_vectors(v));
	;
	v[QVEC] = cross(v[TVEC], edge[0]);
	c[V] = dot(ray, v[QVEC]) * det;
	if (c[V] < 0 || c[U] + c[V] > 1)
		return (free_vectors(v));
	;
	c[T] = dot(edge[1], v[QVEC]) * det;
	free_vectors(v);
	return (c[T]);
}

static double	*get_normal(double *edge[2])
{
	double *normal;

	normal = cross(edge[0], edge[1]);
	normalize(normal);
	return (normal);
}

double			intersect_triangle(void *obj, double ray[3],
									t_params *current, double origin[3])
{
	t_tri	*tri;
	double	*edge[2];
	double	t;

	tri = (t_tri *)obj;
	edge[0] = get_edge(tri->second, tri->first);
	edge[1] = get_edge(tri->third, tri->first);
	t = check_barycentric_coords(origin, tri->first, ray, edge);
	if (t == 0)
	{
		free_edges(edge);
		return (0);
	}
	if (current != NULL)
		set_triangle_params(get_point(origin, ray, t),
							get_normal(edge), tri, current);
	free_edges(edge);
	return (t);
}
