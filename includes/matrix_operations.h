/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:29:19 by meldora           #+#    #+#             */
/*   Updated: 2021/03/16 13:01:50 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_OPERATIONS_H
# define MATRIX_OPERATIONS_H

# include <stdlib.h>
# include "errors.h"

double	**alloc_matrix(void);
double	**matrix_from_quaternion(double q[4]);
void	multiply_by_matrix(double c[3], double **m);
void	free_matrix(double **matrix);

#endif
