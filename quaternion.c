/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:39:49 by meldora           #+#    #+#             */
/*   Updated: 2021/02/01 17:15:51 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/quaternion_operations.h"

#include <stdio.h>

/*
float   get_angle(float u[3], float v[3])
{
    return (acos(dot(u, v) / sqrt(get_norm(u) * get_norm(v))));
}
*/

float	get_angle(float u[3], float v[3])
{
	float numerator;
	float denominator;

	numerator = dot(u, v);
	denominator = sqrt(get_length(u)) * sqrt(get_length(v));
	return (acos(numerator / denominator));
}

void	normalize_quaternion(float q[4])
{
	float norm;

	norm = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
	q[0] /= norm;
	q[1] /= norm;
	q[2] /= norm;
	q[3] /= norm;
}

float	*get_quaternion(float cam[3], float default_camera_direction[3])
{
	float	angle;
	float	sine;
	float	*axis;
	float	*quaternion;

	angle = get_angle(cam, default_camera_direction);
	axis = cross(cam, default_camera_direction);
	sine = sin(angle / 2);
	;
	quaternion = malloc(sizeof(float) * 4);
	;
	quaternion[0] = cos(angle / 2);
	quaternion[1] = axis[0] * sine;
	quaternion[2] = axis[1] * sine;
	quaternion[3] = axis[2] * sine;
	;
	normalize_quaternion(quaternion);
	;
	free(axis);
	return (quaternion);
}