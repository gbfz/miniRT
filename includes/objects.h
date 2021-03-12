/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:04:52 by meldora           #+#    #+#             */
/*   Updated: 2021/03/10 16:37:56 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct	s_sphere
{
	double		*coords;
	double		diameter;
	double		*colors;
}				t_sphere;

typedef struct	s_plane
{
	double		*coords;
	double		*vector;
	double		*colors;
}				t_plane;

typedef struct	s_square
{
	double		*coords;
	double		*vector;
	int			side;
	double		*colors;
	double		**vertices;
}				t_square;

typedef struct	s_cylinder
{
	double		*coords;
	double		*vector;
	double		diameter;
	double		height;
	double		*colors;
	double		*bottom_cap;
	double		m;
}				t_cylinder;

typedef struct	s_tri
{
	double		*first;
	double		*second;
	double		*third;
	double		*colors;
}				t_tri;

#endif
