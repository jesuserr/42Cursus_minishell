/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:03:40 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/27 18:33:49 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Prints out path working directory using getcwd instead of using */
/* environment variable (PWD) in order to avoid failure in case that (PWD) */
/* is not present - No STDIN for this kind of built-in */
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
	ft_printf(STDOUT_FILENO, "%s\n", pwd);
	return (0);
}

/* Prints out all the content of the environment variables */
/* No STDIN for this kind of built-in */
int	built_in_env(t_exec_data *d)
{
	int	i;

	i = 0;
	while ((*d->env)[i])
		ft_printf(STDOUT_FILENO, "%s\n", (*d->env)[i++]);
	return (0);
}

/* Removes variable from environment. If variable name contains any character */
/* that is not alphanumeric or '_' displays an error message */
/* The real unset built-in can delete multiple variables in one commnad line */
/* i.e. "unset PWD PATH LANG ", implemented too */
/* No STDIN/STDOUT for this kind of built-in */
int	built_in_unset(t_exec_data *d)
{
	size_t	i;
	size_t	j;
	char	*var;

	if (!d->exec_args[1])
		return (0);
	j = 1;
	while (d->exec_args[j])
	{
		var = ft_strdup(d->exec_args[j++]);
		i = 0;
		while (i < ft_strlen(var))
		{
			if (!(ft_isalnum((var[i])) || var[i] == '_'))
			{
				d->int_error_code = ERROR_B_UNSET;
				ft_error_handler(var, d);
				break ;
			}
			i++;
		}
		del_var_from_env(d->env, var);
		free (var);
	}
	return (0);
}

/* Prints out the list of arguments provided, if first argument is -n */
/* no newline is sent to terminal at the end of the printing */
/* No STDIN for this kind of built-in */
int	built_in_echo(t_exec_data *d)
{
	int	i;
	int	flag;

	if (!d->exec_args[1])
	{
		ft_printf(STDOUT_FILENO, "\n");
		return (0);
	}
	i = 1;
	flag = 0;
	if (!(ft_strncmp(d->exec_args[1], "-n", 2)) && \
	ft_strlen(d->exec_args[1]) == 2)
	{
		flag = 1;
		i++;
	}
	while (d->exec_args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", d->exec_args[i++]);
		if (d->exec_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (!flag)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
