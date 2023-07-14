/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/14 18:37:33 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_pwd(t_exec_data *d)
{
	int	i;

	i = 0;
	while (ft_strnstr(d->env[i], "PWD=", 4) == NULL)
		i++;
	printf("%s\n", d->env[i] + 4);
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

int	built_in_exec(t_exec_data *d)
{
	//return (built_in_pwd(d));
	//return (built_in_env(d));
	return (built_in_echo(d));
}
