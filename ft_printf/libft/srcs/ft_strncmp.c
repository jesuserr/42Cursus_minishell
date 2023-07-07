/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:27:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/12 12:27:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	if (!n)
		return (0);
	count = 0;
	while (count < n - 1 && s1[count] != 0
		&& s2[count] != 0
		&& (unsigned char) s1[count] == (unsigned char) s2[count])
		count++;
	if ((unsigned char) s1[count] - (unsigned char) s2[count] > 0)
		return (1);
	else if ((unsigned char) s1[count] - (unsigned char) s2[count] < 0)
		return (-1);
	else
		return (0);
}
