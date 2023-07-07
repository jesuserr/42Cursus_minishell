/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:12:39 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/12 16:44:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	count;

	if (!n)
		return (0);
	count = 0;
	while (count < n - 1
		&& ((unsigned char *)s1)[count] == ((unsigned char *)s2)[count])
		count++;
	return (((unsigned char *)s1)[count] - ((unsigned char *)s2)[count]);
}
