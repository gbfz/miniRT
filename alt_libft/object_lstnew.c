/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:23:30 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 12:24:40 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_obj	*object_lstnew(void *object)
{
	t_obj *elem;

	elem = (t_obj *)malloc(sizeof(t_obj));
	if (elem == NULL)
		return (NULL);
	elem->obj = object;
	elem->next = NULL;
	return (elem);
}