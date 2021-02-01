/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:44:01 by meldora           #+#    #+#             */
/*   Updated: 2020/11/03 22:51:16 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char *mydst;
	unsigned char *mysrc;

	if (!src || !dst)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	mydst = (unsigned char *)dst;
	mysrc = (unsigned char *)src;
	while (dstsize-- > 1 && *mysrc)
		*mydst++ = *mysrc++;
	*mydst = '\0';
	return (ft_strlen(src));
}
