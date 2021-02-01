/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:32:51 by meldora           #+#    #+#             */
/*   Updated: 2020/11/10 13:18:33 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	if (!n)
		return (0);
	if (!*one || !*two)
		return (*one - *two);
	while (n-- > 1 && *one && *two)
	{
		if (*one != *two)
			return (*one - *two);
		one++;
		two++;
	}
	return (*one - *two);
}
