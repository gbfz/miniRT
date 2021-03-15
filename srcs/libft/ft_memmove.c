/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:23:20 by meldora           #+#    #+#             */
/*   Updated: 2020/11/10 13:30:36 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (dst);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		d = dst + len - 1;
		s = src + len - 1;
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}
