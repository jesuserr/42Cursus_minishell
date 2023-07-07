/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:35:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/11 20:01:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	count;

	count = 0;
	if (dst == src || !len)
		return (dst);
	if (dst < src)
	{
		while (count < len)
		{
			((char *) dst)[count] = ((char *) src)[count];
			count++;
		}
	}
	else
	{
		while (len > 0)
		{
			((char *) dst)[len - 1] = ((char *) src)[len - 1];
			len--;
		}
	}
	return (dst);
}
