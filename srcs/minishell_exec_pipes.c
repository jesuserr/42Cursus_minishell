/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/24 21:50:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_close_pipe(int pipe)
{
	if (pipe > 2)
		return (close (pipe));
	return (0);
}

void	ft_exec_pipe_parent(t_exec_data *d)
{
	if (d->fd_in < 3 && d->fd_out > 2 && d->pipe_current[WRITE_END] != -1)
	{
		ft_close_pipe(d->pipe_current[WRITE_END]);
	}
	else if (d->fd_in > 2 && d->fd_out < 3 && d->pipe_last[READ_END] != -1)
	{
		ft_close_pipe(d->pipe_last[READ_END]);
	}
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
}

void	ft_exec_pipe_child(t_exec_data *d)
{
	if (d->fd_in < 3 && d->fd_out > 2 && d->pipe_current[WRITE_END] != -1)
	{
		ft_close_pipe(d->pipe_current[READ_END]);
		if (dup2(d->pipe_current[WRITE_END], STDOUT_FILENO) < 0)
			ft_error("dup2: bad file descriptor");
		ft_close_pipe(d->pipe_current[WRITE_END]);
	}
	else if (d->fd_in > 2 && d->fd_out < 3 && d->pipe_last[READ_END] != -1)
	{
		if (dup2(d->pipe_last[READ_END], STDIN_FILENO) < 0)
			ft_error("dup2: bad file descriptor");
		ft_close_pipe(d->pipe_last[READ_END]);
	}
	else if (d->fd_in > 2 && d->fd_out > 2 && d->pipe_last[READ_END] != -1
		&& d->pipe_current[WRITE_END] != -1)
	{
		ft_close_pipe(d->pipe_current[READ_END]);
		if (dup2(d->pipe_last[READ_END], STDIN_FILENO) < 0
			|| dup2(d->pipe_current[WRITE_END], STDOUT_FILENO) < 0)
			ft_error("dup2: bad file descriptor");
		ft_close_pipe(d->pipe_last[READ_END]);
		ft_close_pipe(d->pipe_current[WRITE_END]);
	}
	else
		exec_dups(d);
}
