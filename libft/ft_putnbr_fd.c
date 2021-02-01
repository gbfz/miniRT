/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meldora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:24:56 by meldora           #+#    #+#             */
/*   Updated: 2020/11/09 09:50:18 by meldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_ok_int_fd(int n, int fd)
{
	int divisor;
	int temp;
	int	i;

	temp = n;
	divisor = 1;
	while (temp / 10)
	{
		divisor *= 10;
		temp /= 10;
	}
	while (divisor)
	{
		i = n / divisor + '0';
		write(fd, &i, 1);
		n %= divisor;
		divisor /= 10;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		ft_put_ok_int_fd(n, fd);
	}
	else
		ft_put_ok_int_fd(n, fd);
}
