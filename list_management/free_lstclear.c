/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:36:53 by meldora           #+#    #+#             */
/*   Updated: 2021/03/08 17:52:40 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

void	free_lstclear(t_free **lst)
{
	if ((*lst)->next != NULL)
		free_lstclear(&(*lst)->next);
	free((*lst)->ptr);
	(*lst)->ptr = NULL;
	free(*lst);
	*lst = NULL;
}