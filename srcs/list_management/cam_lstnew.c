/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:25:04 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:00:37 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt_libft.h"

t_cam	*cam_lstnew(void)
{
	t_cam *elem;

	elem = (t_cam *)malloc(sizeof(t_cam));
	if (elem == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
