/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:46 by meldora           #+#    #+#             */
/*   Updated: 2021/03/17 18:33:53 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALT_LIBFT_H
# define ALT_LIBFT_H

# include "../../includes/objects.h"
# include "../../includes/minirt.h"
# include <stdlib.h>

void		object_lstadd_back(t_obj **lst, t_obj *new);
t_obj		*object_lstlast(t_obj *lst);
t_obj		*object_lstnew(void *object, int id);

void		cam_lstadd_back(t_cam **lst, t_cam *new);
t_cam		*cam_lstlast(t_cam *lst);
t_cam		*cam_lstnew(void);
size_t		cam_lstsize(t_cam *lst);

void		light_lstadd_back(t_light **lst, t_light *new);
t_light		*light_lstlast(t_light *lst);
t_light		*light_lstnew(void);

#endif
