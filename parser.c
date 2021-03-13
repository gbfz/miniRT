/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:03:59 by meldora           #+#    #+#             */
/*   Updated: 2021/03/13 13:56:07 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "alt_libft/alt_libft.h"

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
	if (ft_strcmp(id, "R") == 0 && res_present++ == 0)
		ret = parse_res(line, scene);
	else if (ft_strcmp(id, "A") == 0 && amb_present++ == 0)
		ret = parse_amb(line, scene);
	else if (ft_strcmp(id, "c") == 0)
		ret = parse_cam(line, scene);
	else if (ft_strcmp(id, "l") == 0)
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
	if (ft_strcmp(id, "sp") == 0)
		ret = parse_sphere(line, scene);
	else if (ft_strcmp(id, "pl") == 0)
		ret = parse_plane(line, scene);
	else if (ft_strcmp(id, "sq") == 0)
		ret = parse_square(line, scene);
	else if (ft_strcmp(id, "cy") == 0)
		ret = parse_cylinder(line, scene);
	else if (ft_strcmp(id, "tr") == 0)
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
	if (ft_strcmp(id, "R") == 0 || ft_strcmp(id, "A") == 0 || \
			ft_strcmp(id, "c") == 0 || ft_strcmp(id, "l") == 0)
		return (parse_params(id, line, scene));
	if (ft_strcmp(id, "pl") == 0 || ft_strcmp(id, "sp") == 0 || \
			ft_strcmp(id, "sq") == 0 || ft_strcmp(id, "cy") == 0 || \
			ft_strcmp(id, "tr") == 0)
		return (parse_objects(id, line, scene));
	return (-1);
}

int		check_file(int ac, char *filename)
{
	if (ac < 2) // wrong
	{
		printf("no file\n");
		return (-1);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 3, ".rt") != 0)
	{
		printf("wrong file format\n");
		return (-1);
	}
	return (0);
}

t_scene	*new_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		return (NULL);
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
	if (scene == NULL)
		return (NULL);
	line = NULL;
	while (get_next_line(config, &line) > 0)
	{
		if (line[0] != '\0' && line[0] != '#')
			if (parse_line(line, scene) == -1)
				exit(0);
		free(line);
	}
	if (line[0] != '\0' && line[0] != '#')
		if (parse_line(line, scene) == -1)
			exit(0);
	if (scene->res == NULL || scene->amb == NULL)
	{
		ft_putstr_fd("Resolution or ambient lighting missing\n", 2);
		exit(0);
	}
	free(line);
	return (scene);
}
