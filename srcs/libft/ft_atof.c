/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:04:55 by meldora           #+#    #+#             */
/*   Updated: 2021/03/12 20:38:39 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *s)
{
	float	res;
	float	d;
	int		sign;

	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	if (*s == '+')
		s++;
	res = 0;
	while (ft_isdigit(*s) && *s)
		res = res * 10 + (*s++ - '0');
	if (*s == '.')
		s++;
	d = 0.1;
	while (ft_isdigit(*s) && *s)
	{
		res += (*s++ - '0') * d;
		d /= 10;
	}
	return (res * sign);
}