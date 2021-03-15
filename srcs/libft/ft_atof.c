/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <meldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:04:55 by meldora           #+#    #+#             */
/*   Updated: 2021/03/15 21:22:06 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

double	ft_atof(char *s)
{
	double	res;
	double	d;
	double	sign;

	sign = 1;
	while (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
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
	res *= sign;
	printf("res = %f\n", res);
	return (res);
}
