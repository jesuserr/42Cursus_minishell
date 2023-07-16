/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:07:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/16 23:09:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Duplicates input and/or output file descriptors if these have a value */
/* greater than 2, by default they are both set at -1, so the function does */
/* not perform any action */
int	exec_dups(t_exec_data *d)
{
	if (d->fd_in > 2)
	{
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			return (-1);
		}
		close(d->fd_in);
	}
	if (d->fd_out > 2)
	{
		if (dup2(d->fd_out, STDOUT_FILENO) == -1)
		{
			d->int_error_code = ERROR_DUP;
			ft_error_handler(NULL, d);
			free_split(d->exec_args, d->exec_path);
			close(STDIN_FILENO);
			return (-1);
		}
		close(d->fd_out);
	}
	return (0);
}
