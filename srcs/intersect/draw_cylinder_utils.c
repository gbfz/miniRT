/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:54:54 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:55:31 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_equation(double eq[3], double o_c[3],
							double ray[3], t_cylinder *cyl)
{
	eq[0] = 1 - pow(dot(ray, cyl->vector), 2);
	eq[1] = (dot(ray, o_c) - dot(ray, cyl->vector) * dot(o_c, cyl->vector)) * 2;
	eq[2] = dot(o_c, o_c) - pow(dot(o_c, cyl->vector), 2)
			- pow(cyl->diameter / 2, 2);
}
