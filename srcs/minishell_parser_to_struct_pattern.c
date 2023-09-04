/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct_pattern.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:43:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/04 19:06:53 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_pattern_count(char *block, char *pattern)
{
	int		count;
	int		len;

	len = ft_strlen(pattern);
	count = 0;
	block = p2_strnstr(block, pattern, ft_strlen(block));
	while (block)
	{
		block += len;
		if (*block && *block != pattern[0] && *(block - (len + 1))
			!= pattern[0])
			count++;
		block = p2_strnstr(block, pattern, ft_strlen(block));
	}
	return (count);
}

void	p_t_s_pattern_fill1(char *block, char **str)
{
	int		lenblock;
	char	*tmp;

	lenblock = p_t_s_count(block);
	*str = ft_calloc(lenblock + 1, sizeof(char));
	if (!str)
		ft_error("Unable to allocate memory in p_t_s_heredoc_fill");
	ft_strlcpy(*str, block, lenblock + 1);
	if ((*str)[0] == '\"' && (*str)[ft_strlen(*str) - 1] == '\"')
	{
		tmp = ft_strtrim(*str, "\"");
		free (*str);
		*str = tmp;
	}
	else if ((*str)[0] == '\'' && (*str)[ft_strlen(*str) - 1] == '\'')
	{
		tmp = ft_strtrim(*str, "\'");
		free (*str);
		*str = tmp;
	}
}

void	p_t_s_pattern_fill(char *block, char *pattern, char **str)
{
	char	**tstr;
	int		lenpattern;

	tstr = str;
	lenpattern = ft_strlen(pattern);
	block = p2_strnstr(block, pattern, ft_strlen(block));
	while (block)
	{
		block += lenpattern;
		if (*block && *block != pattern[0]
			&& *(block - (lenpattern + 1)) != pattern[0])
		{
			while (*block && *block == ' ')
				block++;
			p_t_s_pattern_fill1(block, tstr);
			tstr++;
		}
		block = p2_strnstr(block, pattern, ft_strlen(block));
	}
}

void	p_t_s_pattern(char *block, char *pattern, int *token_n, char ***t_str)
{
	int	n;

	n = p_t_s_pattern_count(block, pattern);
	if (n)
	{
		*token_n = n;
		*t_str = ft_calloc(n + 1, sizeof(char *));
		if (!*t_str)
			ft_error("Unable to allocate memory in p_t_s_pattern");
		p_t_s_pattern_fill(block, pattern, *t_str);
	}
}
