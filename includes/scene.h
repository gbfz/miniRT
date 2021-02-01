/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:00:10 by meldora           #+#    #+#             */
/*   Updated: 2021/01/31 11:54:45 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct	s_res
{
	int			x;
	int			y;
}				t_res;

typedef struct s_amb
{
	float		ratio;
	float		*colors;
}				t_amb;

typedef	struct		s_cam
{
	int				id;
	float			*coords;
	float			*vector;
	short			angle;
	struct s_cam	*next;
}					t_cam;

typedef struct	s_light
{
	float			*coords;
	float			*colors;
	float			intensity;
	struct s_light	*next;
}					t_light;

typedef struct		s_obj
{
	short			id;
	void			*obj;
	struct s_obj	*next;
}					t_obj;

typedef struct	s_scene
{
	t_res		res;
	t_amb		*amb;
	t_cam		*cam;
	t_light		*light;
	t_obj		*obj_lst;
}				t_scene;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			en;
}				t_img;

#endif
