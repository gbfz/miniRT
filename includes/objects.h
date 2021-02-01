/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:04:52 by meldora           #+#    #+#             */
/*   Updated: 2021/01/31 11:54:26 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_sphere
{
	float		*coords;
	int			diameter;
	float		*colors;
}				t_sphere;

typedef struct	s_plane
{
	float		*coords;
	float		*vector;
	float		*colors;
}				t_plane;

typedef struct	s_square
{
	float		*coords;
	float		*vector;
	int			side;
	float		*colors;
}				t_square;

typedef struct	s_cylinder
{
	float		*coords;
	float		*vector;
	float		diameter;
	float		height;
	float		*colors;
}				t_cylinder;

typedef struct	s_tri
{
	float		*first;
	float		*second;
	float		*third;
	float		*colors;
}				t_tri;

#endif
