/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_check_built_ins.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:13:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/25 21:52:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_strtolower(char *str)
{
	if (!str || !*str)
		return;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += ('a' - 'A');
		str++;
	}
}

int	executor_check_built_ins(t_token *token, t_exec_data *d)
{
	ft_printf(1, "2_Aqui\n");
	d->exec_args = ft_split_quotes(token->cmd, ' ');
	ft_strtrim_quotes(d->exec_args);
	ft_strtolower(d->exec_args[0]);
	if (ft_strncmp(d->exec_args[0], "echo", ft_strlen(d->exec_args[0])))
		return (0);
	else if (ft_strncmp(d->exec_args[0], "cd", ft_strlen(d->exec_args[0])))
		return (0);
	else if (ft_strncmp(d->exec_args[0], "pwd", ft_strlen(d->exec_args[0])))
		return (0);
	else if (ft_strncmp(d->exec_args[0], "export", ft_strlen(d->exec_args[0])))
		return (0);
	else if (ft_strncmp(d->exec_args[0], "unset", ft_strlen(d->exec_args[0])))
		return (0);
	else if (ft_strncmp(d->exec_args[0], "env", ft_strlen(d->exec_args[0])))
		return (0);
	free_split(d->exec_args, d->exec_path);
	ft_printf(1, "1_Aqui\n");
	return (1);
}
