/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:17:44 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 12:18:26 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

void	light_lstadd_back(t_light **lst, t_light *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	light_lstlast(*lst)->next = new;
}