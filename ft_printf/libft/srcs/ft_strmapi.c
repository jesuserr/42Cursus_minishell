/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:05:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/16 20:27:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	count;
	unsigned int	len;
	char			*str;

	len = ft_strlen((char *)s);
	str = (char *) ft_calloc(sizeof(char), (len + 1));
	if (!s || !f || !str)
		return (0);
	count = 0;
	while (count < len)
	{
		str[count] = f(count, s[count]);
		count++;
	}
	return (str);
}
