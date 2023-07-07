/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:04:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/03/01 21:28:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_formatgetsize(t_info *info, va_list *ap)
{
	if (info->width == -100)
		info->width = va_arg(*ap, int);
	if (info->precision == -100)
		info->precision = va_arg(*ap, int);
}

void	ft_format_width(char *value, t_info *info)
{
	int	len;

	len = ft_strlen(value);
	if (info->width > len)
	{
		if (info->flagminus == '-')
		{
			ft_memset(&value[len], ' ', info->width - len);
		}
		else
		{
			ft_memmove(&value[info->width - len], value, info->width);
			ft_memset(value, ' ', info->width - len);
		}
	}
}
