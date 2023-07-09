/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:21:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/09 21:52:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*p_get_first_env(char *tline)
{
	char	*tmp;
	char	*tmp1;
	int		count;

	tmp = strnstr(tline, "$", ft_strlen(tline));
	count = 0;
	tmp1 = tmp;
	while (tmp[count] && tmp[count] != ' ' && tmp[count] != ',')
		count++;
	tmp = tmp1;
	tmp1 = ft_calloc(count + 2, sizeof(char));
	if (!tmp1)
		ft_error("Unable to allocate memory in *p_get_first_env");
	ft_strlcpy(tmp1, tmp + 1, count);
	return (tmp1);
}

char	*p_replace_str(char *dst, char *old, char *new)
{
	char	*tmp;
	char	*fdst;
	char	*str;
	int		count;

	fdst = dst;
	tmp = ft_calloc(ft_strlen(dst) + ft_strlen(new), sizeof(char));
	str = tmp;
	if (!tmp)
		ft_error("Unable to allocate memory in p_replace_str");
	while (*dst != '$')
	{
		*tmp = *dst;
		tmp++;
		dst++;
	}
	count = -1;
	while (++count < (int) ft_strlen(old) + 1)
		dst++;
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
	free (fdst);
	return (str);
}

char	*p_replace_env(char *tline)
{
	char	*tmp;

	while (strnstr(tline, "$", ft_strlen(tline)))
	{
		tmp = p_get_first_env(tline);
		tline = p_replace_str(tline, tmp, getenv(tmp));
		free (tmp);
	}
	return (tline);
}
