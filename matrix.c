/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:10:16 by meldora           #+#    #+#             */
/*   Updated: 2021/01/31 16:35:58 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/matrix_operations.h"

float	**alloc_matrix(void)
{
	float **matrix;

	matrix = malloc(sizeof(*matrix) * 3);
	matrix[0] = malloc(sizeof(float) * 3);
	matrix[1] = malloc(sizeof(float) * 3);
	matrix[2] = malloc(sizeof(float) * 3);
	return (matrix);
}

float	**matrix_from_quaternion(float q[4])
{
	float **matrix;

	matrix = alloc_matrix();
	;
	matrix[0][0] = 2 * (q[0] * q[0] + q[1] * q[1]) - 1;
	matrix[0][1] = 2 * (q[1] * q[2] - q[0] * q[3]);
	matrix[0][2] = 2 * (q[1] * q[3] + q[0] * q[2]);
	;
	matrix[1][0] = 2 * (q[1] * q[2] + q[0] * q[3]);
	matrix[1][1] = 2 * (q[0] * q[0] + q[2] * q[2]) - 1;
	matrix[1][2] = 2 * (q[2] * q[3] - q[0] * q[1]);
	;
	matrix[2][0] = 2 * (q[1] * q[3] - q[0] * q[2]);
	matrix[2][1] = 2 * (q[2] * q[3] + q[0] * q[1]);
	matrix[2][2] = 2 * (q[0] * q[0] + q[3] * q[3]) - 1;
	;
	return (matrix);
}

void	multiply_coords_by_matrix(float c[3], float **m)
{
	float x;
	float y;
	float z;

	x = c[0];
	y = c[1];
	z = c[2];
	;
	c[0] = x * m[0][0] + y * m[0][1] + z * m[0][2];
	c[1] = x * m[1][0] + y * m[1][1] + z * m[1][2];
	c[2] = x * m[2][0] + y * m[2][1] + z * m[2][2];
}

void	free_matrix(float **matrix)
{
	free(matrix[0]);
	free(matrix[1]);
	free(matrix[2]);
	free(matrix);
}