/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_cmds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:59:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/18 12:59:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_cmds(t_list *lst)
{
	t_token		*token;
	t_exec_data	*d;

	while (lst)
	{
		token = lst->content;
		d = ft_calloc(1, sizeof(t_exec_data));
		d->exec_args = ft_split(token->cmd, ' ');
		d->env = g_data.env;
		d->int_error_code = 0;
		d->term_status = 0;
		d->fd_in = -1;
		d->fd_out = -1;
		if (token->cmdin > 2)
			d->fd_in = token->cmdin;
		if (token->cmdout > 2)
			d->fd_out = token->cmdout;
		ft_command_exec(d);
		free(d);
		lst = lst->next;
	}
}
