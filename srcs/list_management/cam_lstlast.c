#include "list_management.h"

t_cam	*cam_lstlast(t_cam *lst)
{
	t_cam *ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
