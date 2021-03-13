/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:15:59 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 14:43:05 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../alt_libft/alt_libft.h"

static void	get_cylinder_cap(t_cylinder *cyl)
{
	cyl->bottom_cap = malloc(sizeof(double) * 3);
	if (cyl->bottom_cap == NULL)
		exit_error("Malloc failed");
	cyl->bottom_cap[0] = cyl->coords[0] - cyl->vector[0] * (cyl->height / 2);
	cyl->bottom_cap[1] = cyl->coords[1] - cyl->vector[1] * (cyl->height / 2);
	cyl->bottom_cap[2] = cyl->coords[2] - cyl->vector[2] * (cyl->height / 2);
}

static int	check_cylinder_line(char *line)
{
	if (count_words(line) != 11)
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (ft_isdigit(*line))
		line += doublelen(line);
	else
		return (1);
	skip_spaces(&line);
	if (ft_isdigit(*line))
		line += doublelen(line);
	else
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void	*parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cyl;

	if (check_cylinder_line(line))
		exit_error("Wrong values for cylinder");
	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	cyl->coords = parse_coords(&line);
	skip_spaces(&line);
	cyl->vector = parse_vector(&line);
	if (cyl->vector == NULL)
		exit_error("Wrong values for cylinder axis");
	cyl->diameter = ft_atof(line);
	if (cyl->diameter < 0)
		exit_error("Wrong cylinder diameter");
	line += doublelen(line);
	skip_spaces(&line);
	cyl->height = ft_atof(line);
	if (cyl->height < 0)
		exit_error("Wrong cylinder height");
	line += doublelen(line);
	skip_spaces(&line);
	cyl->colors = parse_colors(&line);
	if (cyl->colors == NULL)
		exit_error("Wrong values for cylinder colors");
	get_cylinder_cap(cyl);
	object_lstadd_back(&scene->obj_lst, object_lstnew(cyl, 3));
	return (cyl);
}