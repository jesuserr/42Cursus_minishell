/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:41:52 by jesuserr          #+#    #+#             */
/*   Updated: 2023/06/02 11:42:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t		count;

	count = 0;
	while (*s)
	{
		if (ft_strchr(charset, *s))
			count++;
		else
			break ;
		s++;
	}
	return (count);
}
