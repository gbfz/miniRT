/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:08:29 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:37:44 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_OPERATIONS_H
# define VECTOR_OPERATIONS_H

# include <math.h>
# include <stdlib.h>
# include "errors.h"

double	get_length(double v[3]);
void	normalize(double v[3]);
double	dot(double u[3], double v[3]);
double	*cross(double u[3], double v[3]);
double	*get_normalized(double v[3]);

#endif
