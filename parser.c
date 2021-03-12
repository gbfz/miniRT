/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:03:59 by meldora           #+#    #+#             */
/*   Updated: 2021/03/11 19:57:29 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "alt_libft/alt_libft.h"

#include <stdio.h>

void	skip_spaces(char **line)
{
	while (ft_isspace(**line) && **line)
		(*line)++;
}

/*
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
*/

/*
int		count_words(char *line)
{
	int words;
	int dot;

	words = 0;
	while (*line)
	{
		skip_spaces(&line);
		if (*line == ',' || *line == '.')
			line++;
		if (ft_isdigit(*line) || *line == '-')
		{
			printf("%c\n", *line);
			dot = 0;
			line++;
			words++;
			while (ft_isdigit(*line))
			{
				line++;
				if (*line == '.' && dot == 0)
				{
					dot = 1;
					line++;
				}
			}
		}
		else
			return (-1);
	}
	printf("words = %d\n", words);
	return (words);
}
*/

int		count_words(char *line)
{
	int words;
	int dot;

	words = 0;
	while (*line)
	{
		skip_spaces(&line);
		if (*line == '-')
			line++;
		if (ft_isdigit(*line))
		{
			dot = 0;
			words++;
			while (ft_isdigit(*line))
			{
				line++;
				if (*line == '.' && dot == 0)
					line++;
			}
			if (*line == ',')
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
	if (scene->res.x < 0)
	{
		printf("Wrong image width\n");
		exit(0);
	}
	line += intlen(scene->res.x);
	skip_spaces(&line);
	scene->res.y = ft_atoi(line);
	if (scene->res.y < 0)
	{
		printf("Wrong image height\n");
		exit(0);
	}
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

size_t	doublelen(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '-')
		i++;
	while ((ft_isdigit(line[i]) || line[i] == '.') && line[i])
		i++;
	return (i);
}

double	*parse_coords(char **line)
{
	double	*coords;
	short	i;

	coords = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		coords[i] = ft_atof(*line);
		*line += doublelen(*line) + 1;
		i++;
	}
	return (coords);
}

double	*parse_vector(char **line)
{
	double	*vector;
	short	i;
	double	len;

	vector = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		vector[i] = ft_atof(*line);
		if (vector[i] > 1 || vector[i] < -1)
		{
			free(vector);
			return (NULL);
		}
		*line += doublelen(*line) + 1;
		i++;
	}
	len = get_length(vector);
	if (len < 0.9999 || len > 1.0001)
	{
		free(vector);
		printf("Not a unit vector\n");
		exit(1);
		return (NULL);
	}
	return (vector);
}

double	*parse_colors(char **line)
{
	double	*colors;
	short	i;

	colors = malloc(sizeof(double) * 3);
	i = 0;
	while (i <= 2)
	{
		colors[i] = ft_atof(*line);
		if (colors[i] < 0 || colors[i] > 255)
		{
			/*
			free(colors);
			return (NULL);
			*/
			printf("Wrong values in color\n");
			exit(0);
		}
		*line += doublelen(*line) + 1;
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
	if (scene->amb->ratio < 0 || scene->amb->ratio > 1)
	{
		printf("Wrong ambient lighting ratio\n");
		exit(0);
	}
	line += doublelen(line);
	skip_spaces(&line);
	scene->amb->colors = parse_colors(&line);
	if (scene->amb->colors == NULL)
		;//return ERROR
	return (scene);
}

double	**get_matrix(t_cam *cam)
{
	double	*quaternion;
	double	**matrix;
	double	default_camera_direction[3];

	default_camera_direction[0] = 0;
	default_camera_direction[1] = 0;
	default_camera_direction[2] = 1;
	;
	quaternion = get_quaternion(cam->vector, default_camera_direction);
	matrix = matrix_from_quaternion(quaternion);
	;
	free(quaternion);
	return (matrix);
}

void	*parse_cam(char *line, t_scene *scene)
{
	t_cam		*camera;
	static int	id;

	if (count_words(line) != 7)
		return (NULL);
	//camera = cam_lstnew();
	camera = malloc(sizeof(t_cam));
	if (camera == NULL)
		return (NULL);
	camera->next = NULL;
	skip_spaces(&line);
	camera->coords = parse_coords(&line);
	skip_spaces(&line);
	camera->vector = parse_vector(&line);
	if (camera->vector == NULL)
		;//return ERROR
	skip_spaces(&line);
	camera->fov = ft_atoi(line) * M_PI / 180;
	if (camera->fov < 0)
	{
		printf("Wrong field of view\n");
		exit(0);
	}
	camera->id = id++;
	camera->matrix = get_matrix(camera);
	cam_lstadd_back(&scene->cam, camera);
	return (camera);
}

void	*parse_light(char *line, t_scene *scene)
{
	t_light	*light;

	if (count_words(line) != 7)
		return (NULL);
	//light = malloc(sizeof(t_light));
	light = light_lstnew();
	if (light == NULL)
		return (NULL);
	skip_spaces(&line);
	light->coords = parse_coords(&line);
	skip_spaces(&line);
	light->intensity = ft_atof(line);
	if (light->intensity < 0 || light->intensity > 1)
	{
		printf("Wrong light intensity\n");
		exit(0);
	}
	line += doublelen(line);
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
	sphere = malloc(sizeof(t_sphere));
	//sphere = new_sphere();
	if (sphere == NULL)
		return (NULL);
	skip_spaces(&line);
	sphere->coords = parse_coords(&line);
	skip_spaces(&line);
	sphere->diameter = ft_atof(line);
	if (sphere->diameter < 0)
	{
		printf("Wrong sphere diameter\n");
		exit(0);
	}
	line += doublelen(line);
	skip_spaces(&line);
	sphere->colors = parse_colors(&line);
	if (sphere->colors == NULL)
		;//return ERROR
	object_lstadd_back(&scene->obj_lst, object_lstnew(sphere, 0));
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
	object_lstadd_back(&scene->obj_lst, object_lstnew(plane, 1));
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

static void		set_inverted_vector(double inverted_vector[3], double vector[3])
{
	inverted_vector[0] = vector[2];
	inverted_vector[1] = vector[1];
	inverted_vector[2] = vector[0];
	if (inverted_vector[0] == vector[0] && inverted_vector[1] == vector[1]
		&& inverted_vector[2] == vector[2])
	{
		inverted_vector[0] = vector[1];
		inverted_vector[1] = vector[2];
		inverted_vector[2] = vector[0];
	}
}

static double	**alloc_vertices(void)
{
	double **vertices;

	vertices = malloc(sizeof(*vertices) * 4);
	vertices[0] = malloc(sizeof(double) * 3);
	vertices[1] = malloc(sizeof(double) * 3);
	vertices[2] = malloc(sizeof(double) * 3);
	vertices[3] = malloc(sizeof(double) * 3);
	return (vertices);
}

static void		get_planes(double vector[3], double **cross1, double **cross2)
{
	double inverted_vector[3];

	set_inverted_vector(inverted_vector, vector);
	*cross1 = cross(vector, inverted_vector);
	normalize(*cross1);
	*cross2 = cross(vector, *cross1);
	normalize(*cross2);
}

static double	**get_vertices(t_square *sq)
{
	double **vertices;
	double *cross1;
	double *cross2;
	double half_side;

	vertices = alloc_vertices();
	get_planes(sq->vector, &cross1, &cross2);
	half_side = (double)sq->side / 2.0;
	vertices[0][0] = (sq->coords[0] - half_side * cross1[0]) + (half_side * cross2[0]);
	vertices[0][1] = (sq->coords[1] - half_side * cross1[1]) + (half_side * cross2[1]);
	vertices[0][2] = (sq->coords[2] - half_side * cross1[2]) + (half_side * cross2[2]);
	vertices[1][0] = (sq->coords[0] + half_side * cross1[0]) + (half_side * cross2[0]);
	vertices[1][1] = (sq->coords[1] + half_side * cross1[1]) + (half_side * cross2[1]);
	vertices[1][2] = (sq->coords[2] + half_side * cross1[2]) + (half_side * cross2[2]);
	vertices[2][0] = (sq->coords[0] + half_side * cross1[0]) - (half_side * cross2[0]);
	vertices[2][1] = (sq->coords[1] + half_side * cross1[1]) - (half_side * cross2[1]);
	vertices[2][2] = (sq->coords[2] + half_side * cross1[2]) - (half_side * cross2[2]);
	vertices[3][0] = (sq->coords[0] - half_side * cross1[0]) - (half_side * cross2[0]);
	vertices[3][1] = (sq->coords[1] - half_side * cross1[1]) - (half_side * cross2[1]);
	vertices[3][2] = (sq->coords[2] - half_side * cross1[2]) - (half_side * cross2[2]);
	free(cross1);
	free(cross2);
	return (vertices);
}

void	*parse_square(char *line, t_scene *scene)
{
	t_square	*square;

	if (count_words(line) != 10)
		return (NULL);
	//square = malloc(sizeof(t_sphere));
	square = ft_calloc(1, sizeof(t_square));
	if (square == NULL)
		return (NULL);
	skip_spaces(&line);
	square->coords = parse_coords(&line);
	skip_spaces(&line);
	square->vector = parse_vector(&line);
	if (square->vector == NULL)
		;//return ERROR
	skip_spaces(&line);
	square->side = ft_atof(line);
	if (square->side < 0)
	{
		printf("Wrong square size\n");
		exit(0);
	}
	line += intlen(square->side);
	skip_spaces(&line);
	square->colors = parse_colors(&line);
	if (square->colors == NULL)
		;//return ERROR
	square->vertices = get_vertices(square);
	object_lstadd_back(&scene->obj_lst, object_lstnew(square, 2));
	return (square);
}

void	get_cylinder_cap(t_cylinder *cyl)
{
	cyl->bottom_cap = malloc(sizeof(double) * 3);
	cyl->bottom_cap[0] = cyl->coords[0] - cyl->vector[0] * (cyl->height / 2);
	cyl->bottom_cap[1] = cyl->coords[1] - cyl->vector[1] * (cyl->height / 2);
	cyl->bottom_cap[2] = cyl->coords[2] - cyl->vector[2] * (cyl->height / 2);
}

void	*parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cyl;

	if (count_words(line) != 11)
		return (NULL);
	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		return (NULL);
	skip_spaces(&line);
	cyl->coords = parse_coords(&line);
	skip_spaces(&line);
	cyl->vector = parse_vector(&line);
	if (cyl->vector == NULL)
		;//return ERROR
	cyl->diameter = ft_atof(line);
	if (cyl->diameter < 0)
	{
		printf("Wrong cylinder diameter\n");
		exit(0);
	}
	line += doublelen(line);
	skip_spaces(&line);
	cyl->height = ft_atof(line);
	if (cyl->height < 0)
	{
		printf("Wrong cylinder height\n");
		exit(0);
	}
	line += doublelen(line);
	skip_spaces(&line);
	cyl->colors = parse_colors(&line);
	if (cyl->colors == NULL)
		;//return ERROR
	get_cylinder_cap(cyl);
	object_lstadd_back(&scene->obj_lst, object_lstnew(cyl, 3));
	return (cyl);
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
	object_lstadd_back(&scene->obj_lst, object_lstnew(tri, 4));
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
	char	*line = NULL;

	scene = new_scene();
	if (scene == NULL)
		return (NULL);
	while (get_next_line(config, &line) > 0)
	{
		if (line[0] != '\0' && line[0] != '#')
			if (parse_line(line, scene) == -1)
			{
				printf("Error @ %s\nAborting\n", line);
				free(line);
				return (NULL);
			}
		free(line);
		line = NULL;
	}
	if (line[0] != '\0')
		if (parse_line(line, scene) == -1)
		{
			printf("Error @ %s\nAborting\n", line);
			free(line);
			return (NULL);
		}
	if (scene->amb == NULL)
		exit(0);
	free(line);
	return (scene);
}
