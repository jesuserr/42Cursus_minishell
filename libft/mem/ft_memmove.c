/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:38:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/27 13:41:15 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (dst);
	if (((size_t)dst - (size_t)src) > len)
		return (ft_memcpy (dst, src, len));
	else
	{
		while (len > 0)
		{
			len--;
			*((unsigned char *)(dst) + len) = *((unsigned char *)(src) + len);
		}
	}
	return (dst);
}
