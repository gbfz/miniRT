/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:28:14 by meldora           #+#    #+#             */
/*   Updated: 2021/03/08 17:52:57 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

void	free_lstadd_front(t_free **lst, t_free *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}