/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:08:30 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/12 12:19:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	length = ft_strlen (s);
	s = s + length;
	if ((char)c == '\0')
		return ((char *)s++);
	while (length > 0 && *s != (char)c)
	{
		length--;
		s--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
