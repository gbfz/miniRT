#include "list_management.h"

t_img_lst	*img_lstnew(t_img img)
{
	t_img_lst *elem;

	elem = malloc(sizeof(t_img_lst));
	if (elem == NULL)
		return (NULL);
	elem->img = img;
	elem->next = NULL;
	return (elem);
}
