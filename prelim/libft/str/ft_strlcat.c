/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:52:13 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/16 18:17:25 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen (dst);
	len_src = ft_strlen (src);
	j = len_dest;
	i = 0;
	if (dstsize == 0 || dstsize <= len_dest)
		return (len_src + dstsize);
	while (src [i] != '\0' && i < dstsize - len_dest - 1)
	{
		dst [j] = src [i];
		i++;
		j++;
	}
	dst [j] = '\0';
	return (len_dest + len_src);
}
