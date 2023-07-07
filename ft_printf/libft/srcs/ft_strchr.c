/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:27:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/12 12:16:41 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count] != 0)
	{
		if (s[count] == (char) c)
			return ((char *) &s[count]);
		count++;
	}
	if (s[count] == (char) c)
		return ((char *) &s[count]);
	return (0);
}
