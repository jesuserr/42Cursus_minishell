/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/07 01:02:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		execute_cd(t_exec_data *d, char *new_pwd);
int		built_in_cd_error(t_exec_data *d, char *pathname);
void	update_env_pwd(t_exec_data *d, char *new_path, char *old_path);

/* The first two 'if' are to evaluate if empty arguments such as " ", "    " */
/* or "" are being passed. If no argument or '~' is provided the value of */ 
/* $HOME is passed to chdir. If $HOME does not exist, error message according */
/* bash is printed. */
/* In any other cases the argument is passed directly to chdir function */
/* No STDIN/STDOUT for this kind of built-in */
int	built_in_cd(t_exec_data *d)
{
	char	*home_path;

	if (check_empty_string(d->exec_args[1]) && ft_strlen(d->exec_args[1]) >= 1)
	{
		errno = 2;
		return (built_in_cd_error(d, " "));
	}
	if (check_empty_string(d->exec_args[1]) && d->exec_args[1])
		return (0);
	if (check_empty_string(d->exec_args[1]) || \
	(!(ft_strncmp(d->exec_args[1], "~", 1)) && ft_strlen(d->exec_args[1]) == 1))
	{
		home_path = get_env_var(d, "HOME");
		if (!home_path)
			return (built_in_cd_error(d, NULL));
		if (execute_cd(d, home_path) == -1)
		{
			free(home_path);
			return (-1);
		}
		free(home_path);
		return (0);
	}
	else
		return (execute_cd(d, d->exec_args[1]));
}

/* First of all checks if the directory name is longer than 255 characters. */
/* Stores the value of the current PWD, executes chdir command and stores */
/* also the value of the new PWD, and then updates the environment variables */
/* PWD & OLDPWD */
int	execute_cd(t_exec_data *d, char *tmp_pwd)
{
	char	*old_pwd;
	char	*new_pwd;

	if (ft_strlen(tmp_pwd) >= 256)
	{
		errno = 36;
		return (built_in_cd_error(d, tmp_pwd));
	}
	old_pwd = obtain_pwd();
	if (chdir(tmp_pwd) == -1)
		built_in_cd_error(d, tmp_pwd);
	else
	{
		new_pwd = obtain_pwd();
		update_env_pwd(d, new_pwd, old_pwd);
		free(new_pwd);
	}
	free(old_pwd);
	return (0);
}

/* Error handler for the multiple possible errors for cd built-in */
int	built_in_cd_error(t_exec_data *d, char *pathname)
{
	char	*str;

	if (!pathname)
	{
		d->int_error_code = ERROR_B_NOHOME;
		d->term_status = 1;
		ft_error_handler(NULL, d);
		return (0);
	}
	str = ft_strjoin("cd: ", pathname);
	if (errno == 2)
		d->int_error_code = ERROR_NOFILE;
	else if (errno == 20)
		d->int_error_code = ERROR_NODIR;
	else if (errno == 13)
		d->int_error_code = ERROR_NOPERM_CD;
	else if (errno == 36)
		d->int_error_code = ERROR_TOOLONG;
	d->term_status = 1;
	ft_error_handler(str, d);
	free(str);
	return (0);
}

void	update_env_pwd(t_exec_data *d, char *new_path, char *old_path)
{
	char	*new_pwd;
	char	*old_pwd;

	(void) d;
	new_pwd = ft_strjoin("PWD=", new_path);
	add_var_to_env(d->env, new_pwd);
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	add_var_to_env(d->env, old_pwd);
	free (new_pwd);
	free (old_pwd);
	return ;
}
