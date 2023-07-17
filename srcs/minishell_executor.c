/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:07:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 21:08:18 by cescanue         ###   ########.fr       */
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

void	ft_executor_free(t_list **list_cmds)
{
	ft_lstclear(list_cmds, p_t_s_free_token);
	free(*list_cmds);
	free(list_cmds);
}

void	ft_executor(t_list **list_cmds)
{
	t_list	*lst;

	lst = *list_cmds;
	ft_executor_heredoc(lst);
	ft_executor_in_literal(lst);
	if (!ft_executor_in_file(lst) || !ft_executor_out_file(lst)
		|| !ft_executor_out_file_add(lst))
	{
		ft_executor_free(list_cmds);
		return ;
	}
	ft_executor_cmds(lst);
	ft_executor_free(list_cmds);
}
