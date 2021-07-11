#include "../../includes/minirt.h"
#include "../list_management/list_management.h"

static int	check_light_line(char *line)
{
	if (count_words(line) != 7)
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

void		*parse_light(char *line, t_scene *scene)
{
	t_light	*light;

	if (check_light_line(line))
		exit_error("Wrong values for light");
	light = light_lstnew();
	if (light == NULL)
		exit_error("Malloc failed");
	skip_spaces(&line);
	light->coords = parse_coords(&line);
	skip_spaces(&line);
	light->intensity = ft_atof(line);
	if (light->intensity < 0 || light->intensity > 1)
		exit_error("Wrong light intensity");
	line += doublelen(line);
	skip_spaces(&line);
	light->colors = parse_colors(&line);
	if (light->colors == NULL)
		exit_error("Wrong values for light colors");
	light_lstadd_back(&scene->light, light);
	return (light);
}
