/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:19:31 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/17 09:34:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc (((len_s1 + len_s2) + 1) * sizeof(*s3));
	if (s3 == NULL)
		return (0);
	ft_memcpy (s3, s1, len_s1);
	ft_memcpy (s3 + len_s1, s2, len_s2);
	*(s3 + len_s1 + len_s2) = '\0';
	return (s3);
}
