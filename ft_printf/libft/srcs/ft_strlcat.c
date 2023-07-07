/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:40:48 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/12 19:54:37 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	len;
	size_t	r;

	if (!dstsize)
		return (ft_strlen(src));
	else if (dstsize < ft_strlen(dst))
		r = (ft_strlen(src) + dstsize);
	else
		r = ft_strlen(src) + ft_strlen(dst);
	len = ft_strlen(dst);
	count = len;
	while (dstsize && count < dstsize - 1 && src[count - len])
	{
		dst[count] = src[count - len];
		count++;
	}
	dst[count] = 0;
	return (r);
}
