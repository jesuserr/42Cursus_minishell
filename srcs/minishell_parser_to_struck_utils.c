/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struck_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:01:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/31 19:47:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_count(char *block)
{
	int		count;
	char	q;

	count = 0;
	while (*block != ' ' && *block != '|' && *block != ';' && *block
		!= '&' && *block != '>' && *block != '<' && *block)
	{
		if (*block == '\"' || *block == '\'')
		{
			q = *block;
			count++;
			block++;
			while (*block && *block != q)
			{
				count++;
				block++;
			}
		}
		count++;
		block++;
	}
	return (count);
}

char	*p_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	count1;
	int		c;

	c = 0;
	if (!*needle)
		return ((char *) haystack);
	count = 0;
	while (haystack[count] && count < len)
	{
		if (haystack[count] == '"')
			c++;
		if (haystack[count] == '\'' && !(c % 2))
			while (haystack[count] && haystack[++count] != '\'')
				;
		count1 = 0;
		while (needle[count1] && haystack[count + count1] == needle[count1]
			&& count + count1 < len)
			count1++;
		if (!needle[count1])
			return ((char *) &haystack[count]);
		count++;
	}
	return (0);
}

char	*p2_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	count1;

	if (!*needle)
		return ((char *) haystack);
	count = 0;
	while (haystack[count] && count < len)
	{
		if (haystack[count] == '\'')
			while (haystack[count] && haystack[++count] != '\'')
				;
		if (haystack[count] == '"')
			while (haystack[count] && haystack[++count] != '"')
				;
		count1 = 0;
		while (needle[count1] && haystack[count + count1] == needle[count1]
			&& count + count1 < len)
			count1++;
		if (!needle[count1])
			return ((char *) &haystack[count]);
		count++;
	}
	return (0);
}
