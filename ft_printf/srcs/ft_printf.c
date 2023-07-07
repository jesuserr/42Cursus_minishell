/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:06:16 by cescanue          #+#    #+#             */
/*   Updated: 2023/02/17 11:14:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_parseinfo(const char **str, t_info *info)
{
	ft_parseflag(str, info);
	ft_parsewidth(str, info);
	ft_parseprecision(str, info);
	ft_parselength(str, info);
	ft_parsespecifier(str, info);
}

void	ft_printvalue(char *value, t_info *info)
{
	if (value)
	{
		ft_putstr(value, info->sizevalue, info);
		free (value);
	}
	else
		info->cprinted = -1;
}

void	ft_print(const char **str, t_info *info, va_list *ap)
{
	char	*value;

	while (ft_strrchr(*str, '%') && info->cprinted != -1)
	{
		ft_initinfo(info);
		value = 0;
		if (ft_strlen(*str) - ft_strlen(ft_strchr(*str, '%')))
		{
			if (ft_putstr((char *)*str, ft_strlen(*str)
					- ft_strlen(ft_strchr(*str, '%')), info) < 0)
				return ;
		}
		(*str) += ft_strlen(*str) - ft_strlen(ft_strchr(*str, '%')) + 1;
		ft_parseinfo (str, info);
		if (info->specifier)
			value = ft_getvalue(info, ap);
		ft_printvalue(value, info);
	}
	if (info->cprinted != -1 && ft_strlen(*str))
		ft_putstr((char *)*str, ft_strlen(*str), info);
}

int	ft_printf(char const *str, ...)
{
	t_info	info;
	va_list	ap;

	ft_initinfo(&info);
	info.cprinted = 0;
	va_start (ap, str);
	ft_print(&str, &info, &ap);
	va_end (ap);
	return (info.cprinted);
}
