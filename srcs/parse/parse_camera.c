/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:02:05 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 18:36:29 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../list_management/alt_libft.h"

double		**get_matrix(t_cam *cam)
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

static int	check_cam_line(char *line)
{
	if (count_words(line) != 7)
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (check_group(&line))
		return (1);
	skip_spaces(&line);
	if (ft_isdigit(*line))
		while (ft_isdigit(*line))
			line++;
	else
		return (1);
	skip_spaces(&line);
	if (*line != '\0')
		return (1);
	return (0);
}

void		*parse_cam(char *line, t_scene *scene)
{
	t_cam		*camera;

	if (check_cam_line(line))
		exit_error("Wrong values for camera");
	camera = malloc(sizeof(t_cam));
	if (camera == NULL)
		exit_error("Malloc failed");
	camera->next = NULL;
	skip_spaces(&line);
	camera->coords = parse_coords(&line);
	skip_spaces(&line);
	camera->vector = parse_vector(&line);
	if (camera->vector == NULL)
		exit_error("Wrong values for camera direction");
	skip_spaces(&line);
	camera->fov = ft_atoi(line) * M_PI / 180;
	if (camera->fov < 0)
		exit_error("Wrong camera view angle");
	camera->matrix = get_matrix(camera);
	cam_lstadd_back(&scene->cam, camera);
	return (camera);
}
