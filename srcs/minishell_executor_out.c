/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_out.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:33:07 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 21:54:59 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_out_file_error(t_token *t, char *out)
{
	char	strerr[500];

	t->cmdout = 1;
	ft_strlcpy(strerr, out, 500);
	ft_strlcat(strerr, ": Is a directory", 500);
	g_info->last_status = 1;
	ft_error_shell(strerr);
}

int	ft_executor_out_file(t_token *t)
{
	int		count;

	count = -1;
	while (++count < t->n_out)
	{
		t->cmdout = open(t->out[count],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (t->cmdout > 1)
			ft_executor_add_fd(t->cmdout, t);
		else
		{
			ft_executor_out_file_error(t, t->out[count]);
			return (0);
		}
	}
	return (1);
}

int	ft_executor_out_file_add(t_token *t)
{
	int		count;

	count = -1;
	while (++count < t->n_out_add)
	{
		t->cmdout = open(t->out_add[count],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (t->cmdout > 1)
			ft_executor_add_fd(t->cmdout, t);
		else
		{
			ft_executor_out_file_error(t, t->out_add[count]);
			return (0);
		}
	}
	return (1);
}
