/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:07:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/08/01 16:13:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_close_fds(t_token *t)
{
	int	count;

	count = 0;
	while (t->fd_to_close[count] > 0)
	{
		close (t->fd_to_close[count]);
		count++;
	}
}

void	ft_executor_free(t_list ***list_cmds)
{
	ft_lstclear(*list_cmds, p_t_s_free_token);
	free(**list_cmds);
	free(*list_cmds);
	*list_cmds = 0;
}

int	ft_executor_in_order(t_token *token)
{
	if (token->last_in)
	{
		if (token->last_in == 1)
		{
			ft_executor_heredoc(token);
			ft_executor_in_literal(token);
			if (!ft_executor_in_file(token))
				return (0);
		}
		else if (token->last_in == 2)
		{
			ft_executor_in_literal(token);
			if (!ft_executor_in_file(token))
				return (0);
			ft_executor_heredoc(token);
		}
		else if (token->last_in == 3)
		{
			if (!ft_executor_in_file(token))
				return (0);
			ft_executor_heredoc(token);
			ft_executor_in_literal(token);
		}
	}
	return (1);
}

int	ft_executor_out_order(t_token *token)
{
	if (token->last_out)
	{
		if (token->last_out == 1)
		{
			if (!ft_executor_out_file_add(token)
				|| !ft_executor_out_file(token))
				return (0);
		}
		else if (token->last_out == 2)
		{
			if (!ft_executor_out_file(token)
				|| !ft_executor_out_file_add(token))
				return (0);
		}
	}
	return (1);
}

void	ft_executor(t_list ***list_cmds, t_global *gd)
{
	t_list	*lst;
	t_token	*token;

	if (!list_cmds)
		return ;
	lst = **list_cmds;
	if (!ft_executor_check_cmds(lst, gd))
	{
		ft_executor_free(list_cmds);
		return ;
	}
	while (lst)
	{
		token = lst->content;
		if (!ft_executor_in_order(token) || !ft_executor_out_order(token))
		{
			ft_executor_free(list_cmds);
			return ;
		}
		lst = lst->next;
	}
	lst = **list_cmds;
	ft_executor_cmds(lst, gd);
	ft_executor_free(list_cmds);
}
