/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:34:41 by meldora           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:09 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_free	*free_lstnew(void *ptr)
{
	t_free *elem;

	elem = malloc(sizeof(t_free));
	if (elem == NULL)
		return (NULL);
	elem->ptr = ptr;
	elem->next = NULL;
	return (elem);
}