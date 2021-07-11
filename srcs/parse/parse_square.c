#include "../../includes/minirt.h"
#include "../list_management/list_management.h"

static int	check_square_line(char *line)
{
	if (count_words(line) != 10)
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
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void		*parse_square(char *line, t_scene *scene)
{
	t_square	*square;

	if (check_square_line(line))
		exit_error("Wrong values for square");
	square = ft_calloc(1, sizeof(t_square));
	if (square == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	square->coords = parse_coords(&line);
	skip_spaces(&line);
	square->vector = parse_vector(&line);
	if (square->vector == NULL)
		exit_error("Wrong values for square normal");
	skip_spaces(&line);
	square->side = ft_atof(line);
	if (square->side < 0)
		exit_error("Wrong value for square side");
	line += doublelen(line);
	skip_spaces(&line);
	square->colors = parse_colors(&line);
	if (square->colors == NULL)
		exit_error("Wrong values for square colors");
	square->vertices = get_vertices(square);
	object_lstadd_back(&scene->obj_lst, object_lstnew(square, 2));
	return (square);
}
