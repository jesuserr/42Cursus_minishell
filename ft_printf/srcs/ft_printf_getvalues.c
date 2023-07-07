/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getvalues.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:33:06 by cescanue          #+#    #+#             */
/*   Updated: 2023/02/16 19:02:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_getvalue(t_info *info, va_list *ap)
{
	char	*value;

	value = ft_calloc(MAX_MEM_VALUE, sizeof(char));
	if (!value)
		return (0);
	ft_valuetype(value, info, ap);
	return (value);
}

void	ft_gets(char *value, t_info *info, va_list *ap)
{
	char	*temp;
	int		size;

	temp = va_arg(*ap, char *);
	if (!temp)
	{
		if (info->setprecision && info->precision >= (int) ft_strlen(TNULL))
			ft_strlcpy(value, TNULL, ft_strlen(TNULL) + 1);
		else if (!info->setprecision)
			ft_strlcpy(value, TNULL, ft_strlen(TNULL) + 1);
		else
			ft_strlcpy(value, TNULL, info->precision + 1);
	}
	else
	{
		if (info->setprecision)
			size = info->precision;
		else
			size = ft_strlen(temp);
		ft_strlcpy(value, (const char *) temp, size + 1);
	}
	ft_formatgetsize(info, ap);
	ft_format_width(value, info);
	info->sizevalue = ft_strlen(value);
}

void	ft_getc(char *value, t_info *info, va_list *ap)
{
	int	tempc;
	int	temp;
	int	cspecial;

	cspecial = 0;
	tempc = va_arg(*ap, int);
	if (tempc < ' ' || tempc > 127)
	{
		temp = tempc;
		tempc = '1';
		cspecial = 1;
	}
	value[0] = tempc;
	ft_formatgetsize(info, ap);
	ft_format_width(value, info);
	info->sizevalue = ft_strlen(value);
	tempc = 0;
	while (cspecial && tempc < info->sizevalue)
	{
		if (value[tempc] == '1')
			value[tempc] = temp;
		tempc++;
	}
}

void	ft_getpercentage(char *value, t_info *info, va_list *ap)
{
	ft_strlcpy(value, (const char *) &"\%", 2);
	ft_formatgetsize(info, ap);
	ft_format_nprecision(value, info);
	ft_format_nwidth(value, info);
	info->sizevalue = ft_strlen(value);
}

void	ft_valuetype(char *value, t_info *info, va_list *ap)
{
	if (info->specifier == '%')
		ft_getpercentage(value, info, ap);
	else if (info->specifier == 'c')
		ft_getc(value, info, ap);
	else if (info->specifier == 's')
		ft_gets(value, info, ap);
	else if (info->specifier == 'p')
		ft_getp(value, info, ap);
	else if (info->specifier == 'x' || info->specifier == 'X')
		ft_getx(value, info, ap);
	else if (info->specifier == 'd' || info->specifier == 'i')
		ft_getd(value, info, ap);
	else if (info->specifier == 'u')
		ft_getu(value, info, ap);
}
