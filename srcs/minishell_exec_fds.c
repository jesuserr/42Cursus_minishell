/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:07:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/17 18:39:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fd_in_dup(t_exec_data *d);
int	fd_out_dup(t_exec_data *d);

/* Duplicates input and/or output file descriptors if they have a value */
/* greater than 2, by default they are both set at -1, so the function does */
/* not perform any action */
int	exec_dups(t_exec_data *d)
{
	if (fd_in_dup(d) == -1)
		return (-1);
	if (fd_out_dup(d) == -1)
		return (-1);
	return (0);
}

/* Duplicates STDIN and keeps a copy of the original value in order to restore */
/* it later */
int	fd_in_dup(t_exec_data *d)
{
	if (d->fd_in > 2)
	{
		d->saved_fd_in = dup(STDIN_FILENO);
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			return (-1);
		}
		close(d->fd_in);
	}
	return (0);
}

/* Duplicates STDOUT and keeps a copy of the original value in order to restore */
/* it later */
int	fd_out_dup(t_exec_data *d)
{
	if (d->fd_out > 2)
	{
		d->saved_fd_out = dup(STDOUT_FILENO);
		if (dup2(d->fd_out, STDOUT_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			if (d->fd_in > 2)
			{
				close(STDIN_FILENO);
				dup2(d->saved_fd_in, STDIN_FILENO);
				close(d->saved_fd_in);
			}
			return (-1);
		}
		close(d->fd_out);
	}
	return (0);
}

/* Restores one or both file descriptors to their original values */
int	restore_fds(t_exec_data *d)
{
	if (d->fd_in > 2)
	{
		close(STDIN_FILENO);
		if (dup2(d->saved_fd_in, STDIN_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			return (-1);
		}
		close(d->saved_fd_in);
	}
	if (d->fd_out > 2)
	{
		close(STDOUT_FILENO);
		if (dup2(d->saved_fd_out, STDOUT_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			return (-1);
		}
		close(d->saved_fd_out);
	}
	return (0);
}
