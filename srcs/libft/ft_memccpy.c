/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:44:43 by meldora           #+#    #+#             */
/*   Updated: 2020/11/09 09:36:12 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			offset;

	ptr = ft_memchr(src, c, n);
	if (ptr)
	{
		offset = ptr - (unsigned char *)src + 1;
		return (ft_memcpy(dst, src, offset) + offset);
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
