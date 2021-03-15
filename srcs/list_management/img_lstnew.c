/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:53:33 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:01:24 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_img_lst	*img_lstnew(t_img img)
{
	t_img_lst *elem;

	elem = malloc(sizeof(t_img_lst));
	if (elem == NULL)
		return (NULL);
	elem->img = img;
	elem->next = NULL;
	return (elem);
}
