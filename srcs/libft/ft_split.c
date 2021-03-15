/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:22:32 by meldora           #+#    #+#             */
/*   Updated: 2020/11/10 18:12:16 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_counter(const char *s, const char c)
{
	char	*ptr;
	size_t	count;

	ptr = (char *)s;
	count = 0;
	while (*ptr)
	{
		if (*ptr != c)
			count++;
		while (*ptr != c && *ptr)
			ptr++;
		if (*ptr)
			ptr++;
	}
	return (count);
}

static size_t	ft_strclen(const char *s, const char c)
{
	size_t i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void		ft_free(char **res, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char		**ft_sub_split(const char *s, char **res, char c, size_t count)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < count)
	{
		while (*ptr == c && *ptr)
			ptr++;
		len = ft_strclen(ptr, c);
		if (!(res[i] = (char *)malloc(sizeof(char) * (len + 1))))
		{
			ft_free(res, count);
			return (NULL);
		}
		ft_strlcpy(res[i], ptr, len + 1);
		ptr += ft_strlen(res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char			**ft_split(const char *s, char c)
{
	char	**res;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_counter(s, c);
	if (!(res = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	res = ft_sub_split(s, res, c, count);
	return (res);
}
