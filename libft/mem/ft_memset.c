/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:35:53 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/12 13:21:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*copy;

	copy = b;
	while (len > 0)
	{
		*(unsigned char *)(b) = (unsigned char)c;
		b++;
		len--;
	}
	return (copy);
}
