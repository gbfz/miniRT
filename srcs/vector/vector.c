/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:41:09 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:03:07 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector_operations.h"

double	get_length(double v[3])
{
	double length;

	length = v[0] * v[0];
	length += v[1] * v[1];
	length += v[2] * v[2];
	return (sqrt(length));
}

void	normalize(double v[3])
{
	double norm;

	norm = get_length(v);
	v[0] /= norm;
	v[1] /= norm;
	v[2] /= norm;
}

double	dot(double u[3], double v[3])
{
	double dot;

	dot = u[0] * v[0];
	dot += u[1] * v[1];
	dot += u[2] * v[2];
	return (dot);
}

double	*cross(double u[3], double v[3])
{
	double *cross;

	cross = malloc(sizeof(double) * 3);
	if (cross == NULL)
		exit_error("Malloc failed");
	cross[0] = u[1] * v[2] - u[2] * v[1];
	cross[1] = u[2] * v[0] - u[0] * v[2];
	cross[2] = u[0] * v[1] - u[1] * v[0];
	return (cross);
}
