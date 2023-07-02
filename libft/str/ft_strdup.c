/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:02:56 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/16 11:37:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*ptr;
	size_t	bytes;

	bytes = ft_strlen (s1) + 1;
	ptr = (char *)malloc(bytes * (sizeof(*s1)));
	if (ptr == NULL)
		return (0);
	ft_memcpy (ptr, s1, bytes);
	return (ptr);
}
