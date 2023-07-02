/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:47:39 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/16 09:32:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str [i] == ' ' || (str [i] >= '\t' && str [i] <= '\r'))
		i++;
	if (str [i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str [i] == '+')
		i++;
	while (str [i] >= '0' && str [i] <= '9')
	{
		result = result * 10;
		result = result + str [i] - '0';
		i++;
	}
	return (result * sign);
}
