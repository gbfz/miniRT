/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lstadd_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:14:25 by meldora           #+#    #+#             */
/*   Updated: 2021/02/14 19:54:43 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

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