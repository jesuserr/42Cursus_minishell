/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_check_cmds.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:05:27 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/24 15:41:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_check_cmds_error(t_exec_data d)
{
	char		error[500];

	ft_strlcpy(error, d.exec_args[0], 500);
	ft_strlcat(error, ": command not found", 500);
	ft_error_shell(error);
	free_split(d.exec_args, d.exec_path);
}

int	ft_executor_check_cmds2(t_token *token, t_exec_data	*d)
{
	d->exec_args = ft_split_quotes(token->cmd, ' ');
	ft_strtrim_quotes(d->exec_args);
	if (check_empty_string(d->exec_args[0]) == -1)
	{
		ft_error_shell("not command");
		free_split(d->exec_args, d->exec_path);
		return (0);
	}
	d->exec_path = check_usr_path(d);
	if (!d->exec_path && d->term_status)
	{
		ft_executor_check_cmds_error(*d);
		return (0);
	}
	if (!d->exec_path)
		d->exec_path = obtain_path(d);
	if (!d->exec_path)
	{
		ft_executor_check_cmds_error(*d);
		return (0);
	}
	return (1);
}

int	ft_executor_check_cmds(t_list *lst)
{
	t_token		*token;
	t_exec_data	d;

	d.env = g_data.env;
	d.exec_path = 0;
	while (lst)
	{
		token = lst->content;
		if (!ft_executor_check_cmds2(token, &d))
			return (0);
		lst = lst->next;
		free_split(d.exec_args, d.exec_path);
	}
	return (1);
}
