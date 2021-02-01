/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:03:59 by meldora           #+#    #+#             */
/*   Updated: 2021/02/01 15:27:53 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "alt_libft/alt_libft.h"

#include <stdio.h>

#define SCALE 10

void	skip_spaces(char **line)
{
	while (ft_isspace(**line) && **line)
		(*line)++;
}

int		count_words(char *line)
{
	int words;

	words = 0;
	while (*line)
	{
		while (ft_isspace(*line) || *line == ',')
			line++;
		if (ft_isdigit(*line) || *line == '-')
		{
			words++;
			while (ft_isdigit(*line) || *line == '-' || *line == '.')
				line++;
		}
		else
			return (-1);
	}
	return (words);
}

size_t	intlen(int n)
{
	size_t i;

	if (n == -2147483648)
		return (11);
	i = 1;
	if (n < 0)
	{
		i = 2;
		n *= -1;
	}
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	*parse_res(char *line, t_scene *scene)
{
	if(count_words(line) != 2)
		return (NULL);
	skip_spaces(&line);
	scene->res.x = ft_atoi(line);
	line += intlen(scene->res.x);
	skip_spaces(&line);
	scene->res.y = ft_atoi(line);
	if (scene->res.x <= 0 || scene->res.y <= 0)
		return (NULL);
	return (scene);
}

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

size_t	floatlen(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while ((ft_isdigit(line[i]) || line[i] == '.') && line[i])
		i++;
	return (i);
}

float	*parse_coords(char **line)
{
	float	*coords;
	short	i;

	coords = malloc(sizeof(float) * 3);
	i = 0;
	while (i <= 2)
	{
		coords[i] = ft_atof(*line);
		*line += floatlen(*line) + 1;
		i++;
	}
	return (coords);
}

float	*parse_vector(char **line)
{
	float	*vector;
	short	i;

	vector = malloc(sizeof(float) * 3);
	i = 0;
	while (i <= 2)
	{
		vector[i] = ft_atof(*line);
		if (vector[i] > 1 || vector[i] < -1)
		{
			free(vector);
			return (NULL);
		}
		*line += floatlen(*line) + 1;
		i++;
	}
	return (vector);
}

float	*parse_colors(char **line)
{
	float	*colors;
	short	i;

	colors = malloc(sizeof(float) * 3);
	i = 0;
	while (i <= 2)
	{
		colors[i] = ft_atof(*line);
		if (colors[i] < 0 || colors[i] > 255)
		{
			free(colors);
			return (NULL);
		}
		*line += floatlen(*line) + 1;
		i++;
	}
	return (colors);
}

void	*parse_amb(char *line, t_scene *scene)
{
	if (count_words(line) != 4)
		return (NULL);
	scene->amb = malloc(sizeof(t_amb));
	skip_spaces(&line);
	scene->amb->ratio = ft_atof(line);
	line += floatlen(line);
	skip_spaces(&line);
	scene->amb->colors = parse_colors(&line);
	if (scene->amb->colors == NULL)
		;//return ERROR
	return (scene);
}

void	*parse_cam(char *line, t_scene *scene)
{
	t_cam		*camera;
	static int	id;

	if (count_words(line) != 7)
		return (NULL);
	camera = cam_lstnew();
	if (camera == NULL)
		return (NULL);
	skip_spaces(&line);
	camera->coords = parse_coords(&line);
	skip_spaces(&line);
	camera->vector = parse_vector(&line);
	if (camera->vector == NULL)
		;//return ERROR
	skip_spaces(&line);
	camera->angle = ft_atoi(line);
	camera->id = id++;
	cam_lstadd_back(&scene->cam, camera);
	return (camera);
}

void	*parse_light(char *line, t_scene *scene)
{
	t_light	*light;

	if (count_words(line) != 7)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	skip_spaces(&line);
	light->coords = parse_coords(&line);
	skip_spaces(&line);
	light->intensity = ft_atof(line);
	line += floatlen(line);
	skip_spaces(&line);
	light->colors = parse_colors(&line);
	if (light->colors == NULL)
		;//return ERROR
	light_lstadd_back(&scene->light, light);
	return (light);
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

t_sphere	*new_sphere(void)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);
	sphere->colors = NULL;
	return (sphere);
}

void	*parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sphere;

	if (count_words(line) != 7)
		return (NULL);
	sphere = malloc(sizeof(sphere));
	//sphere = new_sphere();
	if (sphere == NULL)
		return (NULL);
	skip_spaces(&line);
	sphere->coords = parse_coords(&line);
	skip_spaces(&line);
	sphere->diameter = ft_atoi(line);
	line += intlen(sphere->diameter);
	skip_spaces(&line);
	sphere->colors = parse_colors(&line);
	if (sphere->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(sphere), 0);
	return (sphere);
}

void	*parse_plane(char *line, t_scene *scene)
{
	t_plane		*plane;
	
	if (count_words(line) != 9)
		return (NULL);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (NULL);
	skip_spaces(&line);
	plane->coords = parse_coords(&line);
	skip_spaces(&line);
	plane->vector = parse_vector(&line);
	if (plane->vector == NULL)
		;//return ERROR
	skip_spaces(&line);
	plane->colors = parse_colors(&line);
	if (plane->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(plane), 1);
	return (plane);
}

t_square	*new_square(void)
{
	t_square *square;

	square = malloc(sizeof(t_square));
	if (square == NULL)
		return (NULL);
	//square->colors = NULL;
	return (square);
}

void	*parse_square(char *line, t_scene *scene)
{
	t_square	*square;

	if (count_words(line) != 10)
		return (NULL);
	square = malloc(sizeof(t_sphere));
	//square = new_square();
	if (square == NULL)
		return (NULL);
	skip_spaces(&line);
	square->coords = parse_coords(&line);
	skip_spaces(&line);
	square->vector = parse_vector(&line);
	if (square->vector == NULL)
		;//return ERROR
	square->side = ft_atoi(line);
	line += intlen(square->side);
	square->colors = parse_colors(&line);
	if (square->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(square), 2);
	return (square);
}

void	*parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;

	if (count_words(line) != 11)
		return (NULL);
	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (NULL);
	skip_spaces(&line);
	cy->coords = parse_coords(&line);
	skip_spaces(&line);
	cy->vector = parse_vector(&line);
	if (cy->vector == NULL)
		;//return ERROR
	cy->diameter = ft_atof(line);
	line += floatlen(line);
	cy->height = ft_atof(line);
	line += floatlen(line);
	cy->colors = parse_colors(&line);
	if (cy->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(cy), 3);
	return (cy);
}

void	*parse_triangle(char *line, t_scene *scene)
{
	t_tri	*tri;

	if (count_words(line) != 12)
		return (NULL);
	tri = malloc(sizeof(t_tri));
	if (tri == NULL)
		return (NULL);
	skip_spaces(&line);
	tri->first = parse_coords(&line);
	skip_spaces(&line);
	tri->second = parse_coords(&line);
	skip_spaces(&line);
	tri->third = parse_coords(&line);
	skip_spaces(&line);
	tri->colors = parse_colors(&line);
	if (tri->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(tri), 4);
	return (tri);
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
	if (ac != 2)
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
	scene->cam = NULL;
	scene->light = NULL;
	scene->obj_lst = NULL;
	return (scene);
}

t_scene	*parser(int config)
{
	t_scene	*scene;
	char	*line;

	scene = new_scene();
	if (scene == NULL)
		return (NULL);
	while (get_next_line(config, &line) > 0)
	{
		if (line[0] != '\0')
		{
			if (parse_line(line, scene) == -1)
			{
				printf("Error @ %s\nAborting\n", line);
				free(line);
				return (NULL);
			}
		}
		free(line);
	}
	return (scene);
}
