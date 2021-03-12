/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:22 by meldora           #+#    #+#             */
/*   Updated: 2021/03/02 16:31:09 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void		skip_spaces(char **line);
int			count_words(char *line);
size_t		intlen(int n);
size_t		doublelen(char *line);
char		*get_id(char *line);

double		*parse_coords(char **line);
double		*parse_vector(char **line);
double		*parse_colors(char **line);

void		*parse_res(char *line, t_scene *scene);
void		*parse_amb(char *line, t_scene *scene);
void		*parse_cam(char *line, t_scene *scene);
void		*parse_light(char *line, t_scene *scene);
int			parse_params(char *id, char *line, t_scene *scene);

t_sphere	*new_sphere(void);
void		*parse_sphere(char *line, t_scene *scene);
void		*parse_plane(char *line, t_scene *scene);
t_square	*new_square(void);
void		*parse_square(char *line, t_scene *scene);

void		*parse_cylinder(char *line, t_scene *scene);
void		get_cylinder_caps(t_cylinder *cyl);
/*
double		*get_bottom_cap(t_cylinder *cyl);
double		*get_top_cap(t_cylinder *cyl);
*/

void		*parse_triangle(char *line, t_scene *scene);
int			parse_objects(char *id, char *line, t_scene *scene);

int			parse_line(char *line, t_scene *scene);

t_scene		*parser(int config);

int			check_file(int ac, char *filename);

t_scene		*new_scene(void);
