#include "list_management.h"

void	object_lstadd_back(t_obj **lst, t_obj *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	object_lstlast(*lst)->next = new;
}
