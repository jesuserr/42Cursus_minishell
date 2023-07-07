/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:27:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/24 17:33:06 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*str;

	str = (unsigned char *) s;
	count = 0;
	while (count < n)
	{
		if (str[count] == (unsigned char) c)
			return ((void *) &str[count]);
		count++;
	}
	return (0);
}
