/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:21:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/10 21:29:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*p_get_first_env(char *tline)
{
	char	*tmp;
	char	*tmp1;
	int		count;

	tmp = p_strnstr(tline, "$", ft_strlen(tline));
	count = 0;
	tmp1 = tmp;
	while (tmp[count] && tmp[count] != ' ' && tmp[count]
		!= ',' && tmp[count] != '\'' && tmp[count] != '"')
		count++;
	tmp = tmp1;
	tmp1 = ft_calloc(count + 2, sizeof(char));
	if (!tmp1)
		ft_error("Unable to allocate memory in *p_get_first_env");
	ft_strlcpy(tmp1, tmp + 1, count);
	return (tmp1);
}

void	p_replace_str1(char *new, char *tmp, char *dst)
{
	while (new && *new)
	{
		*tmp = *new;
		tmp++;
		new++;
	}
	while (*dst)
	{
		*tmp = *dst;
		tmp++;
		dst++;
	}
}

char	*p_replace_str(char *dst, char *old, char *new)
{
	char	*tmp;
	char	*tmp1;
	char	*fdst;
	char	*str;
	int		count;

	fdst = dst;
	tmp = ft_calloc(ft_strlen(dst) + ft_strlen(new), sizeof(char));
	str = tmp;
	if (!tmp)
		ft_error("Unable to allocate memory in p_replace_str");
	tmp1 = p_strnstr(dst, "$", ft_strlen(dst));
	while (dst != tmp1)
	{
		*tmp = *dst;
		tmp++;
		dst++;
	}
	count = -1;
	while (*dst && ++count < (int) ft_strlen(old) + 1)
		dst++;
	p_replace_str1(new, tmp, dst);
	free (fdst);
	return (str);
}

char	*p_replace_env(char *tline)
{
	char	*tmp;

	while (p_strnstr(tline, "$", ft_strlen(tline)))
	{
		tmp = p_get_first_env(tline);
		tline = p_replace_str(tline, tmp, getenv(tmp));
		free (tmp);
	}
	return (tline);
}

char	*p_strnstr(const char *haystack, const char *needle, size_t len)
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
