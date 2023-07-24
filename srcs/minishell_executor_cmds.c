/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_cmds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:59:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/24 15:36:45 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_cmds_init_exec(t_exec_data *d)
{
	d->env = g_data.env;
	d->int_error_code = 0;
	d->term_status = 0;
	d->fd_in = -1;
	d->fd_out = -1;
	d->pipe_current[0] = -1;
	d->pipe_current[1] = -1;
	d->pipe_last[0] = -1;
	d->pipe_last[1] = -1;
}

void	ft_executor_cmds_redi_pipe2(t_token *token, t_exec_data *d, int *p)
{
	if (token->type == T_PIPE && token->cmdout < 3)
	{
		pipe(p);
		d->fd_out = p[1];
		d->pipe_current[0] = p[0];
		d->pipe_current[1] = p[1];
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
		d->pipe_current[0] = -1;
		d->pipe_current[1] = -1;
	}
}

void	ft_executor_cmds_redi_pipe(t_token *token, t_exec_data *d, int *p)
{
	if (p[0] > 2)
	{
		d->fd_in = p[0];
		d->pipe_last[0] = p[0];
		d->pipe_last[1] = p[1];
	}
	else
	{
		d->pipe_last[0] = -1;
		d->pipe_last[1] = -1;
	}
	if (token->cmdin > 2)
		d->fd_in = token->cmdin;
	if (token->cmdout > 2)
		d->fd_out = token->cmdout;
	ft_executor_cmds_redi_pipe2(token, d, p);
}

void	ft_executor_cmds_waitpid(t_list *lst)
{
	t_token		*token;
	t_exec_data	*d;

	while (lst)
	{
		token = lst->content;
		d = token->d;
		waitpid(d->fork_pid, &d->waitpid_status, 0);
		d->term_status = WEXITSTATUS(d->waitpid_status);
		ft_executor_close_fds(token);
		free(d);
		lst = lst->next;
	}
}

void	ft_executor_cmds(t_list *lst)
{
	t_token		*token;
	t_exec_data	*d;
	int			p[2];
	t_list		*lstcopy;

	lstcopy = lst;
	p[0] = -1;
	p[1] = -1;
	while (lst)
	{
		token = lst->content;
		d = ft_calloc(1, sizeof(t_exec_data));
		token->d = d;
		d->exec_args = ft_split_quotes(token->cmd, ' ');
		ft_strtrim_quotes(d->exec_args);
		ft_executor_cmds_init_exec(d);
		ft_executor_cmds_redi_pipe(token, d, p);
		ft_command_exec(d);
		lst = lst->next;
	}
	ft_executor_cmds_waitpid(lstcopy);
}
