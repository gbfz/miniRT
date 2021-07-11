#include "list_management.h"

t_cam	*cam_lstnew(void)
{
	t_cam *elem;

	elem = (t_cam *)malloc(sizeof(t_cam));
	if (elem == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
