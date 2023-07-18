/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:02:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/18 23:42:46 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_parselength(const char **str, t_info *info)
{
	if (**str == 'h')
		info->length = 'h';
	else if (**str == 'l')
		info->length = 'l';
	else if (**str == 'L')
		info->length = 'L';
	if (info->length != 0)
		(*str)++;
}

void	ft_parseprecision(const char **str, t_info *info)
{
	if (**str == '.')
	{
		info->setprecision = 1;
		(*str)++;
		if (**str == '*')
		{
			info->precision = -100;
			(*str)++;
			return ;
		}
		while (**str >= '0' && **str <= '9')
		{
			info->precision *= 10;
			info->precision += **str - '0';
			(*str)++;
		}
	}
}

void	ft_parsewidth(const char **str, t_info *info)
{
	if (**str == '*')
	{
		info->width = -100;
		(*str)++;
		return ;
	}
	while (**str >= '0' && **str <= '9')
	{
		info->width *= 10;
		info->width += **str - '0';
		(*str)++;
	}
}

void	ft_parseflag(const char **str, t_info *info)
{
	while (**str == '-' || **str == '+'
		|| **str == ' ' || **str == '#' || **str == '0')
	{
		if (**str == '-')
			info->flagminus = **str;
		else if (**str == '+')
			info->flagplus = **str;
		else if (**str == ' ')
			info->flagspace = **str;
		else if (**str == '#')
			info->flaghash = **str;
		else if (**str == '0')
			info->flagzero = **str;
		(*str)++;
	}
}

void	ft_parsespecifier(const char **str, t_info *info)
{
	if (**str == 'd' || **str == 'i' || **str == 'u' || **str == 'o'
		|| **str == 'x' || **str == 'X' || **str == 'f' || **str == 'F'
		|| **str == 'e' || **str == 'E' || **str == 'g' || **str == 'G'
		|| **str == 'a' || **str == 'A' || **str == 'c' || **str == 's'
		|| **str == 'p' || **str == 'n' || **str == '%')
	{
		info->specifier = **str;
		(*str)++;
	}
}
