#include "../../includes/minirt.h"
#include "../list_management/list_management.h"

static int	check_sphere_line(char *line)
{
	skip_spaces(&line);
	if (check_group(&line))
		return (0);
	skip_spaces(&line);
	if (ft_isdigit(*line))
		line += doublelen(line);
	skip_spaces(&line);
	if (check_group(&line))
		return (0);
	skip_spaces(&line);
	if (*line != '\0')
		return (0);
	return (1);
}

void		*parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;

	if (check_sphere_line(line) == 0)
		exit_error("Wrong values for sphere");
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	sphere->coords = parse_coords(&line);
	skip_spaces(&line);
	sphere->diameter = ft_atof(line);
	if (sphere->diameter < 0)
		exit_error("Wrong sphere diameter");
	line += doublelen(line);
	skip_spaces(&line);
	sphere->colors = parse_colors(&line);
	if (sphere->colors == NULL)
		exit_error("Wrong values for sphere colors");
	object_lstadd_back(&scene->obj_lst, object_lstnew(sphere, 0));
	return (sphere);
}
