/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:43:36 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/14 22:14:18 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		size;

	if (!len || start >= ft_strlen(s))
		size = 0;
	else if (ft_strlen(s) > (start + len))
		size = len;
	else
		size = ft_strlen(s) - start;
	substr = (char *) malloc (sizeof(char) * (size + 1));
	if (!substr)
		return (0);
	if (size)
		ft_strlcpy(substr, &s[start], size + 1);
	else
		substr[0] = 0;
	return (substr);
}
