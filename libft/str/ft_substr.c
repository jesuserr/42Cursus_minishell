/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:59:59 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/16 17:53:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	length_s;

	if (s == NULL)
		return (0);
	length_s = ft_strlen(s);
	if (start > length_s)
	{
		sub = (char *)malloc (sizeof(*sub));
		if (sub == NULL)
			return (0);
		*sub = 0;
		return (sub);
	}
	if (len > (length_s - start))
		len = length_s - start;
	sub = (char *)malloc ((len + 1) * sizeof(*sub));
	if (sub == NULL)
		return (0);
	ft_memcpy (sub, s + start, len);
	*(sub + len) = '\0';
	return (sub);
}
