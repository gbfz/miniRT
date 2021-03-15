/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:58:47 by meldora           #+#    #+#             */
/*   Updated: 2021/01/26 14:17:01 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(char *str)
{
	char	*ptr;
	int		len;
	int		sign;
	int		result;

	ptr = str;
	while (ft_isspace(*ptr))
		ptr++;
	sign = *ptr == '-' ? -1 : 1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr == '0')
		ptr++;
	len = 0;
	result = 0;
	while (ft_isdigit(*ptr))
	{
		result = result * 10 + (*ptr - '0');
		ptr++;
		len++;
	}
	if (len >= 19)
		return ((-sign - 1) / 2);
	return (result * sign);
}
