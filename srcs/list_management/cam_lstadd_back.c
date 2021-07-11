#include "list_management.h"

void	cam_lstadd_back(t_cam **lst, t_cam *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cam_lstlast(*lst)->next = new;
}
