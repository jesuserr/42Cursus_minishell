/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:14:34 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/13 07:24:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *) malloc (sizeof (char) * (ft_strlen(s) + 1));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
