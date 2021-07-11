#include "list_management.h"

t_img_lst	*img_lstlast(t_img_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
