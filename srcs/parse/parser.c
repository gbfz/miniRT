/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:03:59 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 14:20:25 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../alt_libft/alt_libft.h"

#include <stdio.h>

char	*get_id(char *line)
{
	char	*id;

	id = malloc(1);
	id[0] = 0;
	while (ft_isalpha(*line) && *line)
		if ((id = ft_strappend(id, *line++)) == NULL)
			return (NULL);
	return (id);
}

int		parse_params(char *id, char *line, t_scene *scene)
{
	void			*ret;
	static int		res_present;
	static int		amb_present;
	
	ret = NULL;
	if (ft_strcmp(id, "R\0") == 0 && res_present++ == 0)
		ret = parse_res(line, scene);
	else if (ft_strcmp(id, "A\0") == 0 && amb_present++ == 0)
		ret = parse_amb(line, scene);
	else if (ft_strcmp(id, "c\0") == 0)
		ret = parse_cam(line, scene);
	else if (ft_strcmp(id, "l\0") == 0)
		ret = parse_light(line, scene);
	free(id);
	if (ret == NULL)
		return (-1);
	return (0);
}

int		parse_objects(char *id, char *line, t_scene *scene)
{
	void	*ret;

	ret = NULL;
	if (ft_strcmp(id, "sp\0") == 0)
		ret = parse_sphere(line, scene);
	else if (ft_strcmp(id, "pl\0") == 0)
		ret = parse_plane(line, scene);
	else if (ft_strcmp(id, "sq\0") == 0)
		ret = parse_square(line, scene);
	else if (ft_strcmp(id, "cy\0") == 0)
		ret = parse_cylinder(line, scene);
	else if (ft_strcmp(id, "tr\0") == 0)
		ret = parse_triangle(line, scene);
	free(id);
	if (ret == NULL)
		return (-1);
	return (0);
}

int		parse_line(char *line, t_scene *scene)
{
	char		*id;

	skip_spaces(&line);
	id = get_id(line);
	if (id == NULL)
		return (-1);
	line += ft_strlen(id);
	if (ft_strcmp(id, "R\0") == 0 || ft_strcmp(id, "A\0") == 0 || \
			ft_strcmp(id, "c\0") == 0 || ft_strcmp(id, "l\0") == 0)
		return (parse_params(id, line, scene));
	else if (ft_strcmp(id, "pl\0") == 0 || ft_strcmp(id, "sp\0") == 0 || \
			ft_strcmp(id, "sq\0") == 0 || ft_strcmp(id, "cy\0") == 0 || \
			ft_strcmp(id, "tr\0") == 0)
		return (parse_objects(id, line, scene));
	else
		exit_error("Wrong parameter supplied");
	return (-1);
}

void		check_file(int ac, char **av)
{
	if (ac > 3)
		exit_error("Too many arguments supplied");
	if (ac < 2)
		exit_error("No file provided");
	if (ft_strcmp(av[1] + ft_strlen(av[1]) - 3, ".rt\0") != 0)
		exit_error("Wrong file format");
	if (ac == 3)
		if (ft_strcmp(av[2], "--save\0") != 0)
			exit_error("Wrong second argument (\"--save\" only)");
}

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		exit_error("Malloc failed");
	scene->res = NULL;
	scene->cam = NULL;
	scene->light = NULL;
	scene->obj_lst = NULL;
	scene->intersect[0] = intersect_sphere;
	scene->intersect[1] = intersect_plane;
	scene->intersect[2] = intersect_square;
	scene->intersect[3] = intersect_cylinder;
	scene->intersect[4] = intersect_triangle;
	return (scene);
}

t_scene	*parser(int config)
{
	t_scene	*scene;
	char	*line;

	scene = new_scene();
	line = NULL;
	while (get_next_line(config, &line) > 0)
	{
		if (line[0] != '#' && line[0] != '\0')
			parse_line(line, scene);
		free(line);
	}
	close(config);
	if (line[0] != '#' && line[0] != '\0')
		parse_line(line, scene);
	if (scene->res == NULL || scene->amb == NULL)
		exit_error("Resolution or ambient lighting missing");
	free(line);
	return (scene);
}
