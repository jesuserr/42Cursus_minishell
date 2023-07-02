/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:38:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/12 13:53:03 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*copy;

	if (dst == NULL && src == NULL)
		return (dst);
	copy = dst;
	while (n > 0)
	{
		*(unsigned char *)(dst) = *(unsigned char *)(src);
		dst++;
		src++;
		n--;
	}
	return (copy);
}
