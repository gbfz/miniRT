/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:46 by meldora           #+#    #+#             */
/*   Updated: 2021/03/10 17:49:14 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALT_LIBFT_H
# define ALT_LIBFT_H

# include "../includes/minirt.h"
# include "../includes/objects.h"
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

/*
void		img_lstadd_back(t_img_lst **lst, t_img *new);
t_img_lst	*img_lstlast(t_img_lst *lst);
*/

/*
t_free	*free_lstnew(void *ptr);
void	free_lstadd_front(t_free **lst, t_free *new);
void	free_lstclear(t_free **lst);
*/

#endif
