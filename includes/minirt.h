/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:54:07 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 18:17:05 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <unistd.h>

# include "../minilibx_mms_20200219/mlx.h"
# include "objects.h"
# include "scene.h"
# include "vector_operations.h"
# include "parser.h"
# include "quaternion_operations.h"
# include "matrix_operations.h"
# include "errors.h"

# include "../get_next_line/get_next_line.h"
# include "../srcs/libft/libft.h"

# define X 0
# define Y 1
# define NO_INTERSECTION INT32_MAX
# define PVEC 0
# define QVEC 1
# define TVEC 2
# define U 0
# define V 1
# define T 2
# define FOG 1519.591837 

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img_lst	*img_lst;
	t_img_lst	*lst_start;
	t_img		img;
}				t_data;

void		pixel_put(t_img *img, int pixel[2], int color);
int			switch_to_next_pixel(int pixel[2], t_res *res);
void		set_first_pixel(int pixel[2]);

double		*get_point(double origin[3], double ray[3], double t);

void		null_params(t_params *n, t_params *c);
void		free_current_params(t_params *current);
void		set_nearest_params(t_params *nearest, t_params current);

double		intersect_cylinder(void *obj, double ray[3], t_params *current, double origin[3]);
double		intersect_sphere(void *obj, double ray[3], t_params *current, double origin[3]);
double		intersect_plane(void *obj, double ray[3], t_params *current, double origin[3]);
double		intersect_square(void *obj, double ray[3], t_params *current, double origin[3]);
double		intersect_triangle(void *obj, double ray[3], t_params *current, double origin[3]);

t_img_lst	*img_lstnew(t_img img);
void		img_lstadd_back(t_img_lst **lst, t_img_lst *new);
t_img_lst	*img_lstlast(t_img_lst *lst);

double		get_distance(double a[3], double b[3]);
int			light_has_obstacles(t_params *obj, t_light *light, double cam_ray[3], t_scene *scene);
double		get_intensity(t_light *light, t_params *obj, t_cam *cam, t_scene *scene);
int			get_color(t_params *obj, t_scene *scene, t_cam *cam);
void		render_screenshot(t_img *img, t_res *res);

int			key_hook(int key, t_data *data);
int			exit_hook(int button, int x, int y, t_data *data);

void		init_data(t_data *data, t_scene *scene);
void		free_cam(t_cam *cam);
void		draw_image(t_data *data, t_scene *scene, t_res *res, t_cam *cam);
void		display(t_data *data);

#endif
