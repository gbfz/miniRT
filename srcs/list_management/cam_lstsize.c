#include "list_management.h"

size_t	cam_lstsize(t_cam *lst)
{
	size_t i;

	if (lst == NULL)
		return (0);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
