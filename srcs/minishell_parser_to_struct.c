/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:55:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/14 10:20:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*p_t_s(char *block)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("Unable to allocate memory in p_t_s");
	p_t_s_pattern(block, "<", &token->n_in, &token->in);
	p_t_s_pattern(block, "<<", &token->n_heredoc, &token->heredoc);
	p_t_s_pattern(block, "<<<", &token->n_in_literal, &token->in_literal);
	p_t_s_pattern(block, ">", &token->n_out, &token->out);
	p_t_s_pattern(block, ">>", &token->n_out_add, &token->out_add);
	p_t_s_cmd(block, &token->cmd);
	token->type = p_t_s_type(block);
	return (token);
}
