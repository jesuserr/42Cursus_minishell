/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:03:55 by cescanue          #+#    #+#             */
/*   Updated: 2023/02/06 20:21:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_itoaputchar(int nbr, char **value)
{
	**value = nbr;
	(*value)++;
}

void	ft_itoap2s(unsigned long nbr, char *base, char **value)
{
	unsigned long	len;

	len = ft_strlen(base);
	if (nbr < len)
		ft_itoaputchar(base[nbr], value);
	else if (nbr >= len)
	{
		ft_itoap2s(nbr / len, base, value);
		ft_itoap2s(nbr % len, base, value);
	}
}

void	ft_itoa2s(long long nbr, char *base, char **value)
{
	long long	len;

	len = ft_strlen(base);
	if (nbr < 0)
	{
		nbr *= -1;
		ft_itoaputchar('-', value);
	}
	if (nbr < len)
		ft_itoaputchar(base[nbr], value);
	else if (nbr >= len)
	{
		ft_itoa2s(nbr / len, base, value);
		ft_itoa2s(nbr % len, base, value);
	}
}
