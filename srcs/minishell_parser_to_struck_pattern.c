/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struck_pattern.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:43:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 16:10:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_pattern_count(char *block, char *pattern)
{
	int		count;
	int		len;

	len = ft_strlen(pattern);
	count = 0;
	block = ft_strnstr(block, pattern, ft_strlen(block));
	while (block)
	{
		block += len;
		if (*block && *block != pattern[0] && *(block - (len + 1)) != pattern[0])
			count++;
		block = ft_strnstr(block, pattern, ft_strlen(block));
	}
	return (count);
}
void	p_t_s_pattern_fill1(char *block, char **heredoc)
{
	int	len;

	len = p_t_s_count(block);
	*heredoc = ft_calloc(len + 1, sizeof(char));
	if (!heredoc)
		ft_error("Unable to allocate memory in p_t_s_heredoc_fill");
	ft_strlcpy(*heredoc, block, len + 1);
}

void	p_t_s_pattern_fill(char *block, char *pattern, t_token *token)
{
	char	**heredoc;
	int		len;

	heredoc = token->heredoc;
	len = ft_strlen(pattern);
	block = ft_strnstr(block, pattern, ft_strlen(block));
	while (block)
	{
		block += len;
		if (*block && *block != pattern[0] && *(block - (len + 1)) != pattern[0])
		{
			p_t_s_pattern_fill1(block, heredoc);
			heredoc++;
		}
		block = ft_strnstr(block, pattern, ft_strlen(block));
	}
}

void	p_t_s_pattern(char *block, char *pattern, t_token *token)
{
	int	n;
	int count;
	
	n = p_t_s_pattern_count(block, pattern);
	if (n)
	{
		token->n_heredoc = n;
		token->heredoc = ft_calloc(n, sizeof(char *));
		if (!token->heredoc)
			ft_error("Unable to allocate memory in p_t_s_heredoc");
		p_t_s_pattern_fill(block, pattern, token);
		count = 0;
		while (count < n)
		{
			printf("heredoc:%s\n", token->heredoc[count]);
			count++;
		}
	}
}