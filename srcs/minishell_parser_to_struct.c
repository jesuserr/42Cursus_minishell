/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:55:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/12 21:27:49 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_t_s_heredoc(char *block, t_token *token)
{
	(void) block;
	(void) token;
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
