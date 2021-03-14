/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:10:16 by meldora           #+#    #+#             */
/*   Updated: 2021/03/14 16:24:03 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix_operations.h"

double	**alloc_matrix(void)
{
	double	**matrix;
	int		i;

	matrix = malloc(sizeof(*matrix) * 3);
	if (matrix == NULL)
		exit_error("Malloc failed");
	i = 0;
	while (i < 3)
	{
		matrix[i] = malloc(sizeof(double) * 3);
		if (matrix[i] == NULL)
			exit_error("Malloc failed");
		i++;
	}
	return (matrix);
}

double	**matrix_from_quaternion(double q[4])
{
	double **matrix;

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

void	multiply_by_matrix(double c[3], double **m)
{
	double x;
	double y;
	double z;

	x = c[0];
	y = c[1];
	z = c[2];
	;
	c[0] = x * m[0][0] + y * m[1][0] + z * m[2][0];
	c[1] = x * m[0][1] + y * m[1][1] + z * m[2][1];
	c[2] = x * m[0][2] + y * m[1][2] + z * m[2][2];
}

void	free_matrix(double **matrix)
{
	free(matrix[0]);
	free(matrix[1]);
	free(matrix[2]);
	free(matrix);
}