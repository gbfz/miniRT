#include "list_management.h"

void	img_lstadd_back(t_img_lst **lst, t_img_lst *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	img_lstlast(*lst)->next = new;
}
