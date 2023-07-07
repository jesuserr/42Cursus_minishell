/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:31:44 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/14 23:13:55 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_checkset(char *set, char c)
{
	int	count;

	count = 0;
	while (set[count] && set[count] != c)
		count++;
	if (count < (int) ft_strlen(set))
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		size;
	char	*str;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_checkset((char *)set, s1[start]))
		start++;
	while (end >= 0 && ft_checkset((char *)set, s1[end]))
		end--;
	size = end + 1 - start;
	if (size < 0)
		size = 0;
	str = (char *) ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (0);
	if (size)
		ft_strlcpy(str, &s1[start], size + 1);
	return (str);
}
