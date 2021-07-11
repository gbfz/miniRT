#include "list_management.h"

void	light_lstadd_back(t_light **lst, t_light *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	light_lstlast(*lst)->next = new;
}
