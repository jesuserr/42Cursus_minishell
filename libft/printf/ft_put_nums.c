/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:45:19 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/15 19:14:32 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_number_sign(long long n, int *i, char p_holder)
{
	if ((p_holder == '+' || p_holder == ' ') && n >= 0)
	{
		if (write (1, &p_holder, 1) != 1)
			return (-1);
		(*i)++;
	}
	if (n < 0)
	{
		if (write (1, "-", 1) != 1)
			return (-1);
		(*i)++;
	}
	return (*i);
}

int	ft_put_number(long long n, int *i, char p_holder)
{
	*i = ft_put_number_sign(n, i, p_holder);
	if (*i == -1)
		return (-1);
	if (n < 0)
		n = -n;
	if (n >= 10)
	{
		ft_put_number(n / 10, i, 0);
		if (*i == -1)
			return (-1);
		ft_put_number(n % 10, i, 0);
	}
	else
	{
		n = n + 48;
		if (write (1, &n, 1) != 1)
			*i = -2;
		(*i)++;
	}
	return (*i);
}

int	ft_put_num_hex_s(unsigned long long n, char p_holder, int ptr, int *i)
{
	if (ptr == 1 && p_holder == 'p')
	{
		if (ft_putstr (POINTER_LOW) != 2)
			return (-1);
		*i = *i + 2;
	}
	if (ptr == 1 && p_holder == 'x' && n > 0)
	{
		if (ft_putstr (POINTER_LOW) != 2)
			return (-1);
		*i = *i + 2;
	}
	if (ptr == 1 && p_holder == 'X' && n > 0)
	{
		if (ft_putstr (POINTER_UPP) != 2)
			return (-1);
		*i = *i + 2;
	}
	return (*i);
}

int	ft_put_num_hex(unsigned long long n, char p_holder, int ptr, int *i)
{
	*i = ft_put_num_hex_s(n, p_holder, ptr, i);
	if (*i == -1)
		return (-1);
	if (n >= 16)
	{
		ft_put_num_hex(n / 16, p_holder, 0, i);
		if (*i == -1)
			return (-1);
		ft_put_num_hex(n % 16, p_holder, 0, i);
	}
	else
	{
		if (p_holder == 'x' || p_holder == 'p')
			if (write (1, &(HEX_LOWER[n]), 1) != 1)
				*i = -2;
		if (p_holder == 'X')
			if (write (1, &(HEX_UPPER[n]), 1) != 1)
				*i = -2;
		(*i)++;
	}
	return (*i);
}
