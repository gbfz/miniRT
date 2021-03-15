/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operations.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:28:45 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:37:33 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_OPERATIONS_H
# define QUATERNION_OPERATIONS_H

# include <stdlib.h>
# include <math.h>
# include "vector_operations.h"
# include "errors.h"

#include <stdio.h>

double	get_angle(double u[3], double v[3]);
void	normalize_quaternion(double q[4]);
double	*get_quaternion(double cam[3], double origin[3]);

#endif