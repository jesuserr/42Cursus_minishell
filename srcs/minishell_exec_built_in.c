/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_built_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:14:51 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/26 21:52:25 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void *ft_executor_get_built_in(t_exec_data *d)
{
	char	*tmp;
	int		(*fp)(t_exec_data *d);

	tmp = ft_strdup(d->exec_args[0]);
	ft_strtolower(tmp);
	//if (!ft_strncmp("echo", tmp, ft_strlen(tmp)))
	//	fp = built_in_echo;
	if (!ft_strncmp("cd", tmp, ft_strlen(tmp)))
		fp = built_in_cd;
	else if (!ft_strncmp("pwd", tmp, ft_strlen(tmp)))
		fp = built_in_pwd;
	//else if (!ft_strncmp("export", tmp, ft_strlen(tmp)))
	//	fp = built_in_export;
	else if (!ft_strncmp("unset", tmp, ft_strlen(tmp)))
		fp = built_in_unset;
	else if (!ft_strncmp("env", tmp, ft_strlen(tmp)))
		fp = built_in_env;
	else
		fp = 0;
	free (tmp);
	return (fp);
}

int	ft_command_exec_built_in(t_exec_data *d)
{
	int		(*fp)(t_exec_data *d);
	int		r;
	
	ft_exec_pipe_child(d);
	fp = ft_executor_get_built_in(d);
	if (fp)
		r = fp(d);
	else
		r = 0;
	ft_exec_pipe_parent(d);
	return (r);	
}
