#ifndef LIST_MANAGEMENT_H
# define LIST_MANAGEMENT_H

# include "../../includes/objects.h"
# include "../../includes/minirt.h"
# include <stdlib.h>

void		object_lstadd_back(t_obj **lst, t_obj *new_obj);
t_obj		*object_lstlast(t_obj *lst);
t_obj		*object_lstnew(void *object, int id);

void		cam_lstadd_back(t_cam **lst, t_cam *new_obj);
t_cam		*cam_lstlast(t_cam *lst);
t_cam		*cam_lstnew(void);
size_t		cam_lstsize(t_cam *lst);

void		light_lstadd_back(t_light **lst, t_light *new_obj);
t_light		*light_lstlast(t_light *lst);
t_light		*light_lstnew(void);

#endif
