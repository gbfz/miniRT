/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:26:32 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 12:27:41 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_light	*light_lstnew(void)
{
	t_light *elem;

	elem = (t_light *)malloc(sizeof(t_light));
	if (elem == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}