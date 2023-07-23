/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/23 14:25:56 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_pwd(t_exec_data *d)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		d->int_error_code = ERROR_B_PWD;
		ft_error_handler(NULL, d);
		return (-1);
	}
	if (exec_dups(d) == -1)
		return (-2);
	ft_printf(STDOUT_FILENO, "%s\n", pwd);
	if (restore_fds(d) == -1)
		return (-2);
	return (0);
}

int	built_in_env(t_exec_data *d)
{
	int	i;

	i = 0;
	while (d->env[i])
		printf("%s\n", d->env[i++]);
	return (0);
}

int	built_in_echo(t_exec_data *d)
{
	int	i;

	d->exec_args = ft_split(d->argv[1], ' ');
	i = 1;
	while (d->exec_args[i])
	{
		printf("%s", d->exec_args[i++]);
		if (d->exec_args[i])
			printf(" ");
	}
	printf("\n");
	free_split(d->exec_args, NULL);
	return (0);
}

//return (built_in_env(d));
//return (built_in_echo(d));
int	built_in_exec(t_exec_data *d)
{
	return (built_in_pwd(d));
}
