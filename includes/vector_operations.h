/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:08:29 by meldora           #+#    #+#             */
/*   Updated: 2021/01/31 15:50:28 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_OPERATIONS_H
# define VECTOR_OPERATIONS_H

# include <math.h>
# include <stdlib.h>

float	get_length(float v[3]);
void	normalize(float v[3]);
float	dot(float u[3], float v[3]);
float	*cross(float u[3], float v[3]);
float	*get_normalized(float v[3]);

#endif
