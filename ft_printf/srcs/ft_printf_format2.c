/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:31:10 by cescanue          #+#    #+#             */
/*   Updated: 2023/02/11 00:55:51 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_format_nprecision(char *value, t_info *info)
{
	int	isnegative;
	int	len;

	isnegative = value[0];
	len = ft_strlen(value);
	if (value[0] == '0' && value[1] == 0
		&& info->setprecision && !info->precision)
		value[0] = 0;
	if (info->setprecision && info->precision >= len)
	{
		if (isnegative == '-')
		{
			value[0] = '0';
			len--;
		}
		ft_memmove(&value[info->precision - len], value, info->precision);
		ft_memset(value, '0', info->precision - len);
		if (isnegative == '-')
			value[0] = '-';
	}
}

void	ft_format_nflags(char *value, t_info *info)
{
	int	isnegative;
	int	len;

	isnegative = value[0];
	len = ft_strlen(value);
	if ((info->flagplus == '+' || info->flagspace == ' ') && isnegative != '-')
	{
		ft_memmove(&value[1], value, len);
		if (info->flagspace == ' ')
			value[0] = info->flagspace;
		if (info->flagplus == '+')
			value[0] = info->flagplus;
	}
}

void	ft_format_nwidth(char *value, t_info *info)
{
	int	is;
	int	len;
	int	se;

	is = value[0];
	len = ft_strlen(value);
	if (info->width > len)
	{
		se = ' ';
		if (info->flagzero == '0' && info->flagminus != '-'
			&& !info->setprecision)
			se = '0';
		if (se == '0' && (is == '-' || is == '+' || is == ' '))
			value[0] = '0';
		if (info->flagminus == '-')
			ft_memset(&value[len], se, info->width - len);
		else
		{
			ft_memmove(&value[info->width - len], value, len);
			ft_memset(value, se, info->width - len);
			if (se == '0' && (is == '-' || is == '+' || is == ' '))
				value[0] = is;
		}
	}
}

void	ft_format_xwidth(char *value, t_info *info)
{
	int	len;
	int	se;

	len = ft_strlen(value);
	if (info->width > len)
	{
		se = ' ';
		if (info->flagzero == '0' && info->flagminus != '-'
			&& !info->setprecision)
			se = '0';
		if (se == '0' && info->flaghash == '#' && info->ovalue != 0)
			value[1] = '0';
		if (info->flagminus == '-')
			ft_memset(&value[len], se, info->width - len);
		else
		{
			ft_memmove(&value[info->width - len], value, len);
			ft_memset(value, se, info->width - len);
			if (se == '0' && info->flaghash == '#' && info->ovalue != 0)
				value[1] = info->specifier;
		}
	}
}

void	ft_format_hash(char *value, t_info *info)
{
	if (info->flaghash == '#' && info->ovalue)
	{
		ft_memmove(&value[2], value, ft_strlen(value));
		value[0] = '0';
		value[1] = info->specifier;
	}
}
