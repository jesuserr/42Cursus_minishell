/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:55:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 20:51:30 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_t_s_free_token(void *t)
{
	t_token	*token;

	token = t;
	ft_executor_close_fds(token);
	free(token->fd_to_close);
	free_split(token->heredoc, token->cmd);
	free_split(token->in_literal, 0);
	free_split(token->in, 0);
	free_split(token->out, 0);
	free_split(token->out_add, 0);
	free(token);
}

void	p_t_s_lastinout(char *block, t_token *token)
{
	char	*start;

	start = block;
	while (*block)
		block++;
	while (block != start && *block != '<')
		block--;
	while (*block == '<' && block != start)
	{
		token->last_in++;
		block--;
	}
	if (*block == '<')
		token->last_in++;
	while (*block)
		block++;
	while (block != start && *block != '>')
		block--;
	while (*block == '>' && block != start)
	{
		token->last_out++;
		block--;
	}
	if (*block == '>')
		token->last_out++;
}

t_token	*p_t_s(char *block)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->fd_to_close = ft_calloc(100, sizeof(int));
	if (!token || !token->fd_to_close)
		ft_error("Unable to allocate memory in p_t_s");
	token->cmdout = 1;
	p_t_s_pattern(block, "<", &token->n_in, &token->in);
	ft_strtrim_quotes(token->in);
	p_t_s_pattern(block, "<<", &token->n_heredoc, &token->heredoc);
	ft_strtrim_quotes(token->heredoc);
	p_t_s_pattern(block, "<<<", &token->n_in_literal, &token->in_literal);
	ft_strtrim_quotes(token->in_literal);
	p_t_s_pattern(block, ">", &token->n_out, &token->out);
	ft_strtrim_quotes(token->out);
	p_t_s_pattern(block, ">>", &token->n_out_add, &token->out_add);
	ft_strtrim_quotes(token->out_add);
	p_t_s_cmd(block, &token->cmd);
	p_t_s_lastinout(block, token);
	token->type = p_t_s_type(block);
	return (token);
}
