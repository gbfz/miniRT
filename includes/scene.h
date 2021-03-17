/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:00:10 by meldora           #+#    #+#             */
/*   Updated: 2021/03/16 13:03:18 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct			s_res
{
	int					x;
	int					y;
}						t_res;

typedef struct			s_amb
{
	double				ratio;
	double				*colors;
}						t_amb;

typedef	struct			s_cam
{
	int					id;
	double				*coords;
	double				*vector;
	double				fov;
	double				*ray;
	double				**matrix;
	struct s_cam		*next;
}						t_cam;

typedef struct			s_light
{
	double				*coords;
	double				*colors;
	double				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_obj
{
	int					id;
	void				*obj;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_params
{
	int					id;
	int					distance;
	double				*colors;
	double				*point;
	double				*normal;
}						t_params;

typedef struct			s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					ll;
	int					en;
}						t_img;

typedef struct			s_img_lst
{
	t_img				img;
	struct s_img_lst	*next;
}						t_img_lst;

typedef struct			s_scene
{
	t_res				*res;
	t_amb				*amb;
	t_cam				*cam;
	t_light				*light;
	t_obj				*obj_lst;
	double				(*intersect[5])(void *, double *,
							t_params *, double *);
}						t_scene;

#endif
