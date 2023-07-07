/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getvalues2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:00:27 by cescanue          #+#    #+#             */
/*   Updated: 2023/02/11 00:34:51 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_getp(char *value, t_info *info, va_list *ap)
{
	unsigned long	temp;
	char			*copyvalue;

	copyvalue = value;
	temp = va_arg(*ap, unsigned long);
	if (!temp)
		ft_strlcpy(value, TNIL, ft_strlen(TNIL) + 1);
	else
	{
		ft_strlcpy(value, (const char *) &"0x", 3);
		copyvalue += 2;
		ft_itoap2s(temp, BLHEXADECIMAL, &copyvalue);
	}
	ft_formatgetsize(info, ap);
	ft_format_nprecision(value, info);
	ft_format_nwidth(value, info);
	info->sizevalue = ft_strlen(value);
}

void	ft_getx(char *value, t_info *info, va_list *ap)
{
	unsigned long	temp;
	char			base[20];
	char			*copyvalue;

	copyvalue = value;
	ft_strlcpy(base, BLHEXADECIMAL, ft_strlen(BLHEXADECIMAL) + 1);
	if (info->specifier == 'X')
		ft_strlcpy(base, BUHEXADECIMAL, ft_strlen(BUHEXADECIMAL) + 1);
	temp = va_arg(*ap, unsigned int);
	info->ovalue = temp;
	ft_itoap2s(temp, base, &copyvalue);
	ft_formatgetsize(info, ap);
	ft_format_nprecision(value, info);
	ft_format_hash(value, info);
	ft_format_xwidth(value, info);
	info->sizevalue = ft_strlen(value);
}

void	ft_getd(char *value, t_info *info, va_list *ap)
{
	long	temp;
	char	*copyvalue;

	copyvalue = value;
	temp = va_arg(*ap, int);
	ft_itoa2s(temp, BDECIMAL, &copyvalue);
	ft_formatgetsize(info, ap);
	ft_format_nprecision(value, info);
	ft_format_nflags(value, info);
	ft_format_nwidth(value, info);
	info->sizevalue = ft_strlen(value);
}

void	ft_getu(char *value, t_info *info, va_list *ap)
{
	long	temp;
	char	*copyvalue;

	copyvalue = value;
	temp = va_arg(*ap, unsigned int);
	ft_itoa2s(temp, BDECIMAL, &copyvalue);
	ft_formatgetsize(info, ap);
	ft_format_nprecision(value, info);
	ft_format_nwidth(value, info);
	info->sizevalue = ft_strlen(value);
}
