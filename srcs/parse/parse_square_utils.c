/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:13:33 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 14:07:55 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../alt_libft/alt_libft.h"

static void		set_inverted_vector(double inverted_vector[3], double vector[3])
{
	inverted_vector[0] = vector[2];
	inverted_vector[1] = vector[1];
	inverted_vector[2] = vector[0];
	if (inverted_vector[0] == vector[0] && inverted_vector[1] == vector[1]
		&& inverted_vector[2] == vector[2])
	{
		inverted_vector[0] = vector[1];
		inverted_vector[1] = vector[2];
		inverted_vector[2] = vector[0];
	}
}

static double	**alloc_vertices(void)
{
	double	**vertices;
	int		i;

	vertices = malloc(sizeof(*vertices) * 4);
	if (vertices == NULL)
		exit_error("Malloc failed");
	i = 0;
	while (i < 4)
	{
		vertices[i] = malloc(sizeof(double) * 3);
		if (vertices[i] == NULL)
			exit_error("Malloc failed");
		i++;
	}
	return (vertices);
}

static void		get_planes(double vector[3], double **cross1, double **cross2)
{
	double inverted_vector[3];

	set_inverted_vector(inverted_vector, vector);
	*cross1 = cross(vector, inverted_vector);
	normalize(*cross1);
	*cross2 = cross(vector, *cross1);
	normalize(*cross2);
}

double			**get_vertices(t_square *sq)
{
	double **vertices;
	double *cross1;
	double *cross2;
	double hs;

	vertices = alloc_vertices();
	get_planes(sq->vector, &cross1, &cross2);
	hs = sq->side / 2.0;
	vertices[0][0] = (sq->coords[0] - hs * cross1[0]) + (hs * cross2[0]);
	vertices[0][1] = (sq->coords[1] - hs * cross1[1]) + (hs * cross2[1]);
	vertices[0][2] = (sq->coords[2] - hs * cross1[2]) + (hs * cross2[2]);
	vertices[1][0] = (sq->coords[0] + hs * cross1[0]) + (hs * cross2[0]);
	vertices[1][1] = (sq->coords[1] + hs * cross1[1]) + (hs * cross2[1]);
	vertices[1][2] = (sq->coords[2] + hs * cross1[2]) + (hs * cross2[2]);
	vertices[2][0] = (sq->coords[0] + hs * cross1[0]) - (hs * cross2[0]);
	vertices[2][1] = (sq->coords[1] + hs * cross1[1]) - (hs * cross2[1]);
	vertices[2][2] = (sq->coords[2] + hs * cross1[2]) - (hs * cross2[2]);
	vertices[3][0] = (sq->coords[0] - hs * cross1[0]) - (hs * cross2[0]);
	vertices[3][1] = (sq->coords[1] - hs * cross1[1]) - (hs * cross2[1]);
	vertices[3][2] = (sq->coords[2] - hs * cross1[2]) - (hs * cross2[2]);
	free(cross1);
	free(cross2);
	return (vertices);
}
