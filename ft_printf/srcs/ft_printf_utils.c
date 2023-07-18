/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:42:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/18 23:44:42 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_initinfo(t_info *info)
{
	info->flagminus = -1;
	info->flagplus = -1;
	info->flagspace = -1;
	info->flagzero = -1;
	info->flaghash = -1;
	info->width = 0;
	info->precision = 0;
	info->setprecision = 0;
	info->length = 0;
	info->specifier = 0;
	info->sizevalue = 0;
	info->ovalue = 0;
}

int	ft_putstr(char *str, int size, t_info *info)
{
	if (write (info->writeoutput, str, size) < 0)
		info->cprinted = -1;
	else
		info->cprinted += size;
	return (info->cprinted);
}
