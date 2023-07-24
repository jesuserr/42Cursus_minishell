/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/24 20:19:12 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_cd(t_exec_data *d, char *pathname)
{
	char	*path_slash;
	char	*path_complete;
	char	buf[PATH_MAX];
	char	*pwd;

	if (pathname[0] == '/')
	{
		if (chdir(pathname) == -1)
			built_in_cd_error(d, pathname);
		else
			update_env_pwd(d, pathname);
	}
	else
	{
		pwd = getcwd(buf, PATH_MAX);
		if (!pwd)
		{
			d->int_error_code = ERROR_B_PWD;
			ft_error_handler(NULL, d);
			return (-1);
		}
		path_slash = ft_strjoin(pwd, "/");
		path_complete = ft_strjoin(path_slash, pathname);
		if (chdir(pathname) == -1)
			built_in_cd_error(d, pathname);
		else
			update_env_pwd(d, path_complete);
		double_free(path_slash, path_complete);
	}
	return (0);
}

void	built_in_cd_error(t_exec_data *d, char *pathname)
{
	char	*str;

	str = ft_strjoin("cd: ", pathname);
	if (errno == 2)
	{
		d->int_error_code = ERROR_NOFILE;
		d->term_status = 1;
		ft_error_handler(str, d);
	}
	else if (errno == 20)
	{
		d->int_error_code = ERROR_NODIR;
		d->term_status = 1;
		ft_error_handler(str, d);
	}
	free(str);
	return ;
}

void	update_env_pwd(t_exec_data *d, char *pathname)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*tmp_pwd;

	tmp_pwd = get_env_var(d, "PWD");
	new_pwd = ft_strjoin("PWD=", pathname);
	add_var_to_env(&d->env, new_pwd);
	old_pwd = ft_strjoin("OLDPWD=", tmp_pwd);
	add_var_to_env(&d->env, old_pwd);
	free (new_pwd);
	free (old_pwd);
	free (tmp_pwd);
	return ;
}
