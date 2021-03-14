/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lstlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:22:09 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 12:22:57 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_light	*light_lstlast(t_light *lst)
{
	t_light *ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}