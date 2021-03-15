/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:43:51 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:00:41 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

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
