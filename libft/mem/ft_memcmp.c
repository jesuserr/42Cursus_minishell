/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:08:05 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/13 12:57:09 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)(s1) == *(unsigned char *)(s2))
		{
			s1++;
			s2++;
			n--;
		}
		else
			return (*(unsigned char *)(s1) - *(unsigned char *)(s2));
	}
	return (0);
}
