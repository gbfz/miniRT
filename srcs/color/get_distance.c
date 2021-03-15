/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:46:30 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:42:18 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_distance(double a[3], double b[3])
{
	double distance;

	distance = pow(b[0] - a[0], 2);
	distance += pow(b[1] - a[1], 2);
	distance += pow(b[2] - a[2], 2);
	return (sqrt(distance));
}
