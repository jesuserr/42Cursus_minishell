/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_text_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:45:19 by jesuserr          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	if (write (1, &c, 1) != 1)
		return (-1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		if (write (1, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (*s)
	{
		if (write (1, s++, 1) != 1)
			return (-1);
		i++;
	}
	return (i);
}
