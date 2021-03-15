/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:23:18 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:43:04 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	null_params(t_params *n, t_params *c)
{
	n->point = NULL;
	c->point = NULL;
	n->normal = NULL;
	c->normal = NULL;
}

void	free_current_params(t_params *current)
{
	free(current->point);
	current->point = NULL;
	free(current->normal);
	current->normal = NULL;
}

void	set_nearest_params(t_params *nearest, t_params current)
{
	nearest->colors = current.colors;
	if (nearest->point != NULL)
		free(nearest->point);
	if (nearest->normal != NULL)
		free(nearest->normal);
	nearest->point = current.point;
	nearest->normal = current.normal;
}
