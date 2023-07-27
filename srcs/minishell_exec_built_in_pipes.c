/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_built_in_pipes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:50:10 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/27 21:31:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_built_in_pipe_end(t_exec_data *d)
{
	if (d->fd_in < 3 && d->fd_out > 2 && d->pipe_current[WRITE_END] != -1)
		ft_close_pipe(d->pipe_current[WRITE_END]);
	else if (d->fd_in > 2 && d->fd_out < 3 && d->pipe_last[READ_END] != -1)
		ft_close_pipe(d->pipe_last[READ_END]);
	else if (d->fd_in > 2 && d->fd_out > 2 && d->pipe_last[READ_END] != -1
		&& d->pipe_current[WRITE_END] != -1)
	{
		ft_close_pipe(d->pipe_last[READ_END]);
		ft_close_pipe(d->pipe_current[WRITE_END]);
	}
	else
	{
		ft_close_pipe(d->pipe_last[READ_END]);
		ft_close_pipe(d->pipe_current[WRITE_END]);
	}
	restore_fds(d);
}

void	ft_exec_built_in_pipe_start_case3(t_exec_data *d)
{
	if (dup2(d->pipe_last[READ_END], STDIN_FILENO) < 0
		|| dup2(d->pipe_current[WRITE_END], STDOUT_FILENO) < 0)
		ft_error("dup2: bad file descriptor");
	if (d->n_out > 0 && d->redi_out > 2 && d->n_in > 0 && d->redi_in > 2)
	{
		if (dup2(d->redi_in, STDIN_FILENO) == -1
			|| dup2(d->redi_out, STDOUT_FILENO) == -1)
			ft_error("dup2: bad file descriptor");
	}
	else if (d->n_in > 0 && d->redi_in > 2)
	{
		if (dup2(d->redi_in, STDIN_FILENO) == -1)
			ft_error("dup2: bad file descriptor");
	}
	else if (d->n_out > 0 && d->redi_out > 2)
	{
		if (dup2(d->redi_out, STDOUT_FILENO) == -1)
			ft_error("dup2: bad file descriptor");
	}
}

void	ft_exec_built_in_pipe_start_case2(t_exec_data *d)
{
	if (dup2(d->pipe_last[READ_END], STDIN_FILENO) < 0)
		ft_error("dup2: bad file descriptor");
	if (d->n_in > 0 && d->redi_in > 2)
	{
		if (dup2(d->redi_in, STDIN_FILENO) == -1)
			ft_error("dup2: bad file descriptor");
	}
}

void	ft_exec_built_in_pipe_start(t_exec_data *d)
{
	d->saved_fd_out = dup(STDOUT_FILENO);
	d->saved_fd_in = dup(STDIN_FILENO);
	if (d->saved_fd_out == -1 || d->saved_fd_out == -1)
		ft_error("dup: bad file descriptor");
	if (d->fd_in < 3 && d->fd_out > 2 && d->pipe_current[WRITE_END] != -1)
	{
		if (dup2(d->pipe_current[WRITE_END], STDOUT_FILENO) < 0)
			ft_error("dup2: bad file descriptor");
		if (d->n_out > 0 && d->redi_out > 2)
		{
			if (dup2(d->redi_out, STDOUT_FILENO) == -1)
				ft_error("dup2: bad file descriptor");
		}
	}
	else if (d->fd_in > 2 && d->fd_out < 3 && d->pipe_last[READ_END] != -1)
		ft_exec_built_in_pipe_start_case2(d);
	else if (d->fd_in > 2 && d->fd_out > 2 && d->pipe_last[READ_END] != -1
		&& d->pipe_current[WRITE_END] != -1)
		ft_exec_built_in_pipe_start_case3(d);
	else
		exec_dups(d);
}
