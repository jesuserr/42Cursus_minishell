/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:32:07 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/23 09:37:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_number(long int number)
{
	int	digits;

	if (number == 0)
		return (1);
	digits = 0;
	while (number != 0)
	{
		number = number / 10;
		digits++;
	}
	return (digits);
}

static int	power_of_10(int power)
{
	int	nb;

	if (power == 0)
		return (1);
	nb = 10;
	while (power > 1)
	{
		nb = nb * 10;
		power--;
	}
	return (nb);
}

static int	find_sign(long int *n)
{
	int	sign;

	sign = 0;
	if (*n < 0)
	{
		sign = 1;
		*n *= -1;
	}
	return (sign);
}

char	*ft_itoa(int n)
{
	int			digits;
	int			sign;
	int			divisor;
	long int	number;
	char		*s;

	number = n;
	sign = find_sign(&number);
	digits = digits_number(number);
	s = (char *)malloc((digits + sign + 1) * sizeof(char));
	if (!s)
		return (0);
	if (sign == 1)
		*s++ = '-';
	divisor = power_of_10 (digits - 1);
	while (divisor > 0)
	{
		*s++ = number / divisor + '0';
		number = number - (divisor * (number / divisor));
		divisor = divisor / 10;
	}
	*s = 0;
	return (s - digits - sign);
}
