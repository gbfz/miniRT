/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:39:49 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:32:07 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/quaternion_operations.h"

double	get_angle(double u[3], double v[3])
{
	double numerator;
	double denominator;

	numerator = dot(u, v);
	denominator = sqrt(get_length(u)) * sqrt(get_length(v));
	return (acos(numerator / denominator));
}

void	normalize_quaternion(double q[4])
{
	double norm;

	norm = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
	q[0] /= norm;
	q[1] /= norm;
	q[2] /= norm;
	q[3] /= norm;
}

double	*get_quaternion(double cam[3], double default_camera_direction[3])
{
	double	angle;
	double	sine;
	double	*axis;
	double	*quaternion;

	angle = get_angle(cam, default_camera_direction);
	axis = cross(cam, default_camera_direction);
	if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0)
		axis[1] = 1;
	sine = sin(angle / 2);
	;
	quaternion = malloc(sizeof(double) * 4);
	if (quaternion == NULL)
		exit_error("Malloc failed");
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