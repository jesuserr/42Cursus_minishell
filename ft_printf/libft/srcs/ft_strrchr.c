/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:27:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/12 16:32:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	count;

	count = ft_strlen(s);
	while (count != 0)
	{
		if (s[count] == (char) c)
			return ((char *) &s[count]);
		count--;
	}
	if (s[count] == (char) c)
		return ((char *) &s[count]);
	return (0);
}
