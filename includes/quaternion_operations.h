/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operations.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:28:45 by meldora           #+#    #+#             */
/*   Updated: 2021/01/27 12:21:37 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_OPERATIONS_H
# define QUATERNION_OPERATIONS_H

# include <stdlib.h>
# include <math.h>
# include "vector_operations.h"

#include <stdio.h>

float	get_angle(float u[3], float v[3]);
void	normalize_quaternion(float q[4]);
float	*get_quaternion(float cam[3], float origin[3]);

#endif