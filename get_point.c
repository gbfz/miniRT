/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:38:37 by meldora           #+#    #+#             */
/*   Updated: 2021/03/02 16:29:30 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

double	*get_point(double origin[3], double ray[3], double t)
{
	double *point;

	point = malloc(sizeof(double) * 3);
	point[0] = origin[0] + ray[0] * t;
	point[1] = origin[1] + ray[1] * t;
	point[2] = origin[2] + ray[2] * t;
	return (point);
}