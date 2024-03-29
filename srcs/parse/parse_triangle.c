#include "../../includes/minirt.h"
#include "../list_management/list_management.h"

static int	check_triangle_line(char *line)
{
	if (count_words(line) != 12)
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
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void		*parse_triangle(char *line, t_scene *scene)
{
	t_tri	*tri;

	if (check_triangle_line(line))
		exit_error("Wrong values for triangle");
	tri = malloc(sizeof(t_tri));
	if (tri == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	tri->first = parse_coords(&line);
	skip_spaces(&line);
	tri->second = parse_coords(&line);
	skip_spaces(&line);
	tri->third = parse_coords(&line);
	skip_spaces(&line);
	tri->colors = parse_colors(&line);
	if (tri->colors == NULL)
		exit_error("Wrong values for triangle colors");
	object_lstadd_back(&scene->obj_lst, object_lstnew(tri, 4));
	return (tri);
}
