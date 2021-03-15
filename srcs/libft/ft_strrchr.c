/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:19:36 by meldora           #+#    #+#             */
/*   Updated: 2020/11/09 12:06:23 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*hold;

	hold = NULL;
	ptr = (char *)s;
	if (*ptr == (char)c)
		hold = ptr;
	while (*ptr)
	{
		ptr++;
		if (*ptr == (char)c)
			hold = ptr;
	}
	return (hold);
}
