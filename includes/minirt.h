/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:54:07 by meldora           #+#    #+#             */
/*   Updated: 2021/03/11 14:12:35 by meldora          ###   ########.fr       */
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

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define X 0
# define Y 1
# define NO_INTERSECTION INT32_MAX
# define PVEC 0
# define QVEC 1
# define TVEC 2
# define U 0
# define V 1
# define T 2
# ifndef DENS
#  define DENS 0
# endif
# define FOG 0.438 * 1.7 / 0.00049

typedef struct		s_free
{
	void			*ptr;
	struct s_free	*next;
}					t_free;

void	pixel_put(t_img *img, int pixel[2], int color);
double	*get_point(double origin[3], double ray[3], double t);
double	intersect_cylinder(void *obj, double ray[3], t_params *current, double origin[3]);
double	intersect_sphere(void *obj, double ray[3], t_params *current, double origin[3]);
double	intersect_plane(void *obj, double ray[3], t_params *current, double origin[3]);
double	intersect_square(void *obj, double ray[3], t_params *current, double origin[3]);
double	intersect_triangle(void *obj, double ray[3], t_params *current, double origin[3]);

/*
void	default_move(void *obj, t_cam *cam);
void	move_triangle(void *obj, t_cam *cam);
*/

t_img_lst	*img_lstnew(t_img img);
void	img_lstadd_back(t_img_lst **lst, t_img_lst *new);
t_img_lst	*img_lstlast(t_img_lst *lst);

//void	default_rotate(void *obj, double **matrix);
void	rotate_sphere(void *obj, double **matrix);
void	rotate_plane(void *obj, double **matrix);
void	rotate_square(void *obj, double **matrix);
void	rotate_cylinder(void *obj, double **matrix);
void	rotate_triangle(void *obj, double **matrix);

int		get_color(t_params *obj, t_scene *scene, t_cam *cam);
void	render_screenshot(t_img *img, t_res *res);

#endif
