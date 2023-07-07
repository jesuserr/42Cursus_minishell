/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:36:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/16 20:44:50 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	count;
	unsigned int	len;

	len = ft_strlen((char *)s);
	if (!s || !f)
		return ;
	count = 0;
	while (count < len)
	{
		f(count, &s[count]);
		count++;
	}
}
