#include "list_management.h"

t_light	*light_lstnew(void)
{
	t_light *elem;

	elem = (t_light *)malloc(sizeof(t_light));
	if (elem == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
