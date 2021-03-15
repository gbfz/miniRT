/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:01:25 by meldora           #+#    #+#             */
/*   Updated: 2020/11/20 17:23:33 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	char	*hay;
	size_t	litlen;

	hay = (char *)big;
	if (big == lit || !*lit)
		return (hay);
	if (!len)
		return (NULL);
	litlen = ft_strlen(lit);
	while (ft_strncmp(hay, lit, litlen) && *hay && --len)
		hay++;
	if (!*hay || len < litlen)
		return (NULL);
	return (hay);
}
