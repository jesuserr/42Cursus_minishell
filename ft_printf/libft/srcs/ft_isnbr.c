/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:25:10 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/07 22:03:54 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isnbr(const char *str)
{
	int		count;
	long	nbr;

	nbr = 0;
	count = 0;
	if (str[count] == '+' || str[count] == '-')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		nbr *= 10;
		nbr += str[count] - 48;
		count++;
	}
	if (count && !nbr && (ft_isalpha(str[count - 1])
			|| str[count - 1] == '+' || str[count - 1] == '-'))
		return (0);
	else if (str[count] == 0 || str[count] == ' ')
		return (count);
	return (0);
}
