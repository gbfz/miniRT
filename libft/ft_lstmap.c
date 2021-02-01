/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:56:18 by meldora           #+#    #+#             */
/*   Updated: 2020/11/19 18:38:04 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newptr;

	if (!lst || !f)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (NULL);
	newptr = newlst;
	lst = lst->next;
	while (lst)
	{
		newptr->next = ft_lstnew(f(lst->content));
		if (!newptr->next)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		newptr = newptr->next;
		lst = lst->next;
	}
	return (newlst);
}
