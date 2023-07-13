/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:55:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 13:40:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_heredoc_count(char *block)
{
	int		count;
	int		count1;

	count = 0;
	while (*block)
	{
		if (*block == '<')
		{
			count1 = 0;
			while (*block == '<')
			{
				block++;
				count1++;
			}
			while (*block == ' ')
				block++;
			if (count1 == 2)
				count++;
		}
		else
			block++;
	}
	return (count);
}

int	p_t_s_count(char *block)
{

	(void) block;
	return 0;
}

void	p_t_s_heredoc_fill(char *block, t_token *token)
{
	int		count1;
	int		len;

	(void) token;
	while (*block)
	{
		if (*block == '<')
		{
			count1 = 0;
			while (*block == '<')
			{
				block++;
				count1++;
			}
			while (*block == ' ')
				block++;
			if (count1 == 2)
			{
				len = p_t_s_count(block);
			}
		}
		else
			block++;
	}
}

void	p_t_s_heredoc(char *block, t_token *token)
{
	int	n;

	n =  p_t_s_heredoc_count(block);
	if (n)
	{
		token->n_heredoc = n;
		token->heredoc = ft_calloc(n, sizeof(char *));
		if (!token->heredoc)
			ft_error("Unable to allocate memory in p_t_s_heredoc");
		p_t_s_heredoc_fill(block, token);
	}
}

void	p_t_s(char *block)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("Unable to allocate memory in p_t_s");
	p_t_s_heredoc(block, token);
	//from here is temporal
	printf("->%s\n", block);
	free (token);
}
