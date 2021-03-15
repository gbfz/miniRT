/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 20:25:03 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:42:48 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_cam(t_cam *cam)
{
	free(cam->coords);
	free(cam->vector);
	free_matrix(cam->matrix);
	free(cam);
}
