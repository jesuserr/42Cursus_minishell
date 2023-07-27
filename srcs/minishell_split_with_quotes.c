/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_with_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:26:30 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/27 17:34:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	count_substrings(char const *s, char c)
{
	int		flag;
	int		flag_dbl_quotes;
	int		flag_sngl_quotes;
	size_t	n;

	flag = 0;
	flag_dbl_quotes = 0;
	flag_sngl_quotes = 0;
	n = 0;
	while (*s)
	{
		if (*s == '"')
			flag_dbl_quotes = !flag_dbl_quotes;
		if (*s == '\'')
			flag_sngl_quotes = !flag_sngl_quotes;
		if (*s == c && flag_dbl_quotes == 0 && flag_sngl_quotes == 0)
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

void	get_string(char const **string, size_t *string_len, char c)
{
	int	fl_d_quotes;
	int	fl_s_quotes;

	fl_d_quotes = 0;
	fl_s_quotes = 0;
	*string += *string_len;
	*string_len = 0;
	while (**string && **string == c)
		(*string)++;
	while ((*string)[*string_len])
	{
		if ((*string)[*string_len] == '"')
			fl_d_quotes = !fl_d_quotes;
		if ((*string)[*string_len] == '\'')
			fl_s_quotes = !fl_s_quotes;
		if ((*string)[*string_len] == c && fl_d_quotes == 0 && fl_s_quotes == 0)
			return ;
		(*string_len)++;
	}
}

/* Modified version of ft_split function, if the delimiter 'c' is between */
/* double or single quotes, is not taken into account and no split is done  */
char	**ft_split_quotes(char const *s, char c)
{
	char		**final;
	char const	*string;
	size_t		string_len;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	j = count_substrings(s, c);
	final = (char **)ft_calloc(sizeof(char *), (j + 1));
	if (!final)
		return (NULL);
	i = 0;
	string = s;
	string_len = 0;
	while (i < j)
	{
		get_string(&string, &string_len, c);
		final[i] = (char *)ft_calloc(sizeof(char), (string_len + 1));
		if (!final[i])
			return (free_split(final, NULL));
		ft_strlcpy(final[i++], string, string_len + 1);
	}
	final[i] = NULL;
	return (final);
}

void	ft_strtrim_quotes(char **strs)
{
	char	*tmp;

	while (*strs)
	{
		tmp = ft_strtrim(*strs, " ");
		free(*strs);
		*strs = tmp;
		tmp = ft_strtrim(*strs, "\"");
		if (ft_strlen(tmp) != ft_strlen(*strs))
		{
			free(*strs);
			*strs = tmp;
		}
		else
		{
			free(*strs);
			*strs = tmp;
			tmp = ft_strtrim(*strs, "'");
			free(*strs);
			*strs = tmp;
		}
		strs++;
	}
}
