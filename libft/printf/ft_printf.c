/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:21:44 by jesuserr          #+#    #+#             */
/*   Updated: 2023/02/13 10:38:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_actions(char const *flag, va_list arg)
{
	int	i;

	i = 0;
	if ((*flag) == '%')
		return (ft_putchar('%'));
	else if (*flag == 'c')
		return (ft_putchar(va_arg (arg, int)));
	else if (*flag == 's' || (*flag == ' ' && *(flag + 1) == 's'))
		return (ft_putstr(va_arg (arg, char *)));
	else if (*flag == 'd' || *flag == 'i')
		return (ft_put_number(va_arg (arg, int), &i, 0));
	else if ((*flag == '+' || *flag == ' ')
		&& (*(flag + 1) == 'd' || *(flag + 1) == 'i'))
		return (ft_put_number(va_arg (arg, int), &i, *flag));
	else if (*flag == 'u')
		return (ft_put_number(va_arg (arg, unsigned int), &i, 0));
	else if (*flag == 'x' || *flag == 'X')
		return (ft_put_num_hex(va_arg (arg, unsigned int), *flag, 0, &i));
	else if (*flag == 'p')
		return (ft_put_num_hex(va_arg (arg, unsigned long long), *flag, 1, &i));
	else if (*flag == '#'
		&& (*(flag + 1) == 'X' || *(flag + 1) == 'x'))
		return (ft_put_num_hex(va_arg (arg, unsigned int), *(flag + 1), 1, &i));
	return (i);
}

static int	ft_evaluate(char const *hold, va_list args)
{
	int	i;
	int	j;

	i = 0;
	while (*hold)
	{
		if (*hold != '%')
		{
			if (write (1, hold++, 1) != 1)
				return (-1);
			i++;
		}
		else
		{
			hold++;
			j = ft_actions (hold++, args);
			if (*(hold - 1) == '#' || *(hold - 1) == '+' || *(hold - 1) == ' ')
				hold++;
			if (j == -1)
				return (-1);
			i = i + j;
		}
	}
	return (i);
}

int	ft_printf(char const *hold, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start (args, hold);
	i = ft_evaluate (hold, args);
	va_end (args);
	return (i);
}
