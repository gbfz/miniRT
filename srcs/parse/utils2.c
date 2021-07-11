#include "../../includes/minirt.h"
#include "../list_management/list_management.h"

char	*get_id(char *line)
{
	char	*id;

	id = malloc(1);
	id[0] = '\0';
	while (ft_isalpha(*line) && *line)
		if ((id = ft_strappend(id, *line++)) == NULL)
			exit_error("Malloc failed");
	return (id);
}

void	check_file(int ac, char **av)
{
	if (ac > 3)
		exit_error("Too many arguments supplied");
	if (ac < 2)
		exit_error("No file");
	if (ft_strcmp(av[1] + ft_strlen(av[1]) - 3, ".rt") != 0)
		exit_error("Wrong file format");
	if (ac == 3)
		if (ft_strcmp(av[2], "--save") != 0)
			exit_error("Wrong second argument (\"--save\" only)");
}
