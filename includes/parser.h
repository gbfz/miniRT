/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:59:22 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 20:23:54 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		skip_spaces(char **line);
int			count_words(char *line);
size_t		intlen(int n);
size_t		doublelen(char *line);
int			ft_isnumber(char *str);
int			check_group(char **line);
char		*get_id(char *line);

double		*parse_coords(char **line);
double		*parse_vector(char **line);
double		*parse_colors(char **line);

void		*parse_res(char *line, t_scene *scene);
void		*parse_amb(char *line, t_scene *scene);
void		*parse_cam(char *line, t_scene *scene);
void		*parse_light(char *line, t_scene *scene);

t_sphere	*new_sphere(void);
void		*parse_sphere(char *line, t_scene *scene);
void		*parse_plane(char *line, t_scene *scene);
double		**get_vertices(t_square *sq);
t_square	*new_square(void);
void		*parse_square(char *line, t_scene *scene);

void		*parse_cylinder(char *line, t_scene *scene);
void		get_cylinder_caps(t_cylinder *cyl);

void		*parse_triangle(char *line, t_scene *scene);

t_scene		*parser(int config);

void		check_file(int ac, char **av);
