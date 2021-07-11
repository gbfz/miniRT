#include "list_management.h"

t_light	*light_lstlast(t_light *lst)
{
	t_light *ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
