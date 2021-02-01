/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:29:19 by meldora           #+#    #+#             */
/*   Updated: 2021/01/27 12:21:33 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_OPERATIONS_H
# define MATRIX_OPERATIONS_H

# include <stdlib.h>


#include <stdio.h>

float	**alloc_matrix(void);
float	**matrix_from_quaternion(float q[4]);
void	multiply_coords_by_matrix(float c[3], float **m);
void	free_matrix(float **matrix);

#endif