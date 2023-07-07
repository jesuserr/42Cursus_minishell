/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:17:10 by cescanue          #+#    #+#             */
/*   Updated: 2023/01/18 18:46:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	countwords(const char *s, char c)
{
	int	count;
	int	count1;
	int	words;

	count = 0;
	words = 0;
	while (s[count])
	{
		while (s[count] && s[count] == c)
			count++;
		count1 = count;
		while (s[count1] && s[count1] != c)
			count1++;
		if (count1 - count)
			words++;
		count = count1;
	}
	return (words);
}

char	**ft_freea(char **astr)
{
	int	index;

	index = 0;
	while (astr[index])
	{
		free(astr[index]);
		index++;
	}
	free(astr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		sdat[3];
	char	**astr;

	astr = (char **)malloc(sizeof(char *) * ((sdat[2] = countwords(s, c)) + 1));
	if (!s || !astr)
		return (0);
	ft_memset (sdat, 0, sizeof(int) * 3);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			sdat[1] = 0;
			while (*(s + sdat[1]) && *(s + sdat[1]) != c)
				sdat[1]++;
			astr[sdat[0]] = ft_substr(s, 0, sdat[1]);
			if (!astr[sdat[0]])
				return (ft_freea(astr));
			sdat[0]++;
			s += sdat[1];
		}
	}
	astr[sdat[0]] = 0;
	return (astr);
}
