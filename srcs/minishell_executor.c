/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:07:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 12:11:43 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_list **list_cmds)
{
	t_list		*lst;
	int			mypipe[2];
	t_exec_data	*t_exec;
	t_token		*t;
	int			count;
	int			*pipelst;
	pid_t		*pidlst;
	int			lstsize;
	
	mypipe[0] = -1;
	mypipe[1] = -1;
	count = 0;
	lst = *list_cmds;
	lstsize = ft_lstsize(lst);
	pipelst = ft_calloc(ft_lstsize(lst) + 1, sizeof(int));
	pidlst = ft_calloc(ft_lstsize(lst) + 1, sizeof(pid_t));
	while (lst)
	{
		t_exec = ft_calloc(1, sizeof(t_exec_data));
		t = ((t_token *)lst->content);
		t_exec->exec_args = ft_split(t->cmd, ' ');
		t_exec->argv = 0;
		t_exec->env = g_data.env;
		t_exec->int_error_code = 0;
		t_exec->term_status = 0;
		//t_exec->exec_path = NULL;	// Not needed can be deleted
		t_exec->pipein[0] = -1;
		t_exec->pipein[1] = -1;
		t_exec->pipeout[0] = -1;
		t_exec->pipeout[1] = -1;
		if (mypipe[0] > -1)
		{
			t_exec->pipein[0] = mypipe[0];
			t_exec->pipein[1] = mypipe[1];
		}
		if (t->type == 1)
		{
			pipe(mypipe);
			t_exec->pipeout[0] = mypipe[0];
			t_exec->pipeout[1] = mypipe[1];
		}
		else
		{
			mypipe[0] = -1;
			mypipe[1] = -1;
		}
		ft_command_exec(t_exec);
		pidlst[count] = t_exec->fork_pid;
		pipelst[count] = t_exec->pipeout[1];
		free_split(t_exec->env, NULL);
		free(t_exec);
		lst = lst->next;
		count++;
	}
	count = 0;
	while (count < lstsize)
	{
		waitpid(pidlst[count], NULL, 0);
		if (pipelst[count] > -1)
			close (pipelst[count]);
		count++;
	}
	ft_lstclear(list_cmds, p_t_s_free_token);
	free(pipelst);
	free(pidlst);
	free(*list_cmds);
	free(list_cmds);
}
