/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:41:09 by meldora           #+#    #+#             */
/*   Updated: 2021/02/01 17:15:02 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vector_operations.h"

float	get_length(float v[3])
{
	float length;

	length = v[0] * v[0];
	length += v[1] * v[1];
	length += v[2] * v[2];
	return (length);
}

void	normalize(float v[3])
{
	float norm;

	norm = sqrt(get_length(v));
	v[0] /= norm;
	v[1] /= norm;
	v[2] /= norm;
}

float	dot(float u[3], float v[3])
{
	float dot;

	dot = u[0] * v[0];
	dot += u[1] * v[1];
	dot += u[2] * v[2];
	return (dot);
}

float	*cross(float u[3], float v[3])
{
	float *cross;

	cross = malloc(sizeof(float) * 3);
	cross[0] = u[1] * v[2] - u[2] * v[1];
	cross[1] = u[2] * v[0] - u[0] * v[2];
	cross[2] = u[0] * v[1] - u[1] * v[0];
	return (cross);
}

float	*get_normalized(float v[3])
{
	float *r;

	r = malloc(sizeof(float) * 3);
	r[0] = v[0];
	r[1] = v[1];
	r[2] = v[2];
	normalize(r);
	return (r);
}