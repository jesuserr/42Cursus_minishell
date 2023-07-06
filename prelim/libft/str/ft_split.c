/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:40:22 by jesuserr          #+#    #+#             */
/*   Updated: 2023/01/25 09:31:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_memory(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

static size_t	count_substrings(char const *s, char c)
{
	int		flag;
	size_t	n;

	flag = 0;
	n = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		if (*s != c && flag == 0)
		{
			flag = 1;
			n++;
		}
		s++;
	}
	return (n);
}

static void	get_string(char const **string, size_t *string_len, char c)
{
	*string += *string_len;
	*string_len = 0;
	while (**string && **string == c)
		(*string)++;
	while ((*string)[*string_len])
	{
		if ((*string)[*string_len] == c)
			return ;
		(*string_len)++;
	}
}

char	**ft_split(char const *s, char c)
{
	char		**final;
	char const	*string;
	size_t		string_len;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	j = count_substrings(s, c);
	final = (char **)malloc(sizeof(char *) * (j + 1));
	if (!final)
		return (NULL);
	i = 0;
	string = s;
	string_len = 0;
	while (i < j)
	{
		get_string(&string, &string_len, c);
		final[i] = (char *)malloc(sizeof(char) * (string_len + 1));
		if (!final[i])
			return (free_memory(final));
		ft_strlcpy(final[i++], string, string_len + 1);
	}
	final[i] = NULL;
	return (final);
}
