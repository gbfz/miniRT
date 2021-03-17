/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:11:31 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 18:36:03 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../list_management/alt_libft.h"

static int	check_plane_line(char *line)
{
	if (count_words(line) != 9)
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void		*parse_plane(char *line, t_scene *scene)
{
	t_plane		*plane;

	if (check_plane_line(line))
		exit_error("Wrong values for plane");
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	plane->coords = parse_coords(&line);
	skip_spaces(&line);
	plane->vector = parse_vector(&line);
	if (plane->vector == NULL)
		exit_error("Wrong values for plane normal");
	skip_spaces(&line);
	plane->colors = parse_colors(&line);
	if (plane->colors == NULL)
		exit_error("Wrong values for plane colors");
	object_lstadd_back(&scene->obj_lst, object_lstnew(plane, 1));
	return (plane);
}
