/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:54:28 by meldora           #+#    #+#             */
/*   Updated: 2020/11/10 14:33:04 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int i, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (i >= ft_strlen(s))
	{
		len = 1;
		i = ft_strlen(s);
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + i, len + 1);
	return (res);
}
