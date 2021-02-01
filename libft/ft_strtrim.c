/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:22:03 by meldora           #+#    #+#             */
/*   Updated: 2020/11/19 16:39:26 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_offset(const char *s1, const char *set, int start, int dir)
{
	int i;
	int check;

	i = start;
	check = i == 0 ? ft_strlen(s1) - 1 : 0;
	while (i != check)
	{
		if (!ft_strchr(set, s1[i]))
			return (i);
		i += dir;
	}
	return (0);
}

char			*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	if (!*s1)
		return ((char *)s1);
	start = ft_offset(s1, set, 0, 1);
	end = ft_offset(s1, set, ft_strlen(s1) - 1, -1) + 1;
	if (start == end - 1)
		end--;
	return (ft_substr(s1, start, end - start));
}
