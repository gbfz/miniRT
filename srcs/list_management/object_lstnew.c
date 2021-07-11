#include "list_management.h"

t_obj	*object_lstnew(void *object, int id)
{
	t_obj *elem;

	elem = malloc(sizeof(t_obj));
	if (elem == NULL)
		return (NULL);
	elem->obj = object;
	elem->id = id;
	elem->next = NULL;
	return (elem);
}
