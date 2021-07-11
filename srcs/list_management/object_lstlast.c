#include "list_management.h"

t_obj	*object_lstlast(t_obj *lst)
{
	t_obj *ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
