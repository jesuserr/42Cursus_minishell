/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:01:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/08 21:59:03 by cescanue         ###   ########.fr       */
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

void	p_strnstr1(const char *h, const char *n, size_t *c, size_t *c1)
{
	if (n[*c1] && h[*c + *c1] == n[*c1]
		&& *c + *c1 && (h[*c + *c1 + 1] == ' '
			|| h[*c + *c1 + 1] == 0))
		(*c)++;
}

char	*p_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	count1;
	int		dq;

	count = 0;
	dq = 0;
	while (haystack[count] && count < len)
	{
		if (haystack[count] == '\"')
		dq++;
		if (haystack[count] == '\'' && !(dq % 2))
			while (haystack[++count] && haystack[++count] != '\'')
				;
		count1 = 0;
		p_strnstr1(haystack, needle, &count, &count1);
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
