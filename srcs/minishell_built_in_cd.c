/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/24 21:57:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_cd_error(t_exec_data *d, char *pathname);
void	update_env_pwd(t_exec_data *d, char *pathname, char *old_pwd);
char	*obtain_pwd(t_exec_data *d);

int	built_in_cd(t_exec_data *d, char *pathname)
{
	char	*path_slash;
	char	*path_complete;	
	char	*pwd;

	if (pathname[0] == '.' && pathname[1] == '\0')
		return (0);
	pwd = obtain_pwd(d);
	if (!pwd)
		return (-1);
	if (pathname[0] == '/')
	{
		if (chdir(pathname) == -1)
			built_in_cd_error(d, pathname);
		else
			update_env_pwd(d, pathname, pwd);
	}
	else
	{
		path_slash = ft_strjoin(pwd, "/");
		path_complete = ft_strjoin(path_slash, pathname);
		if (chdir(pathname) == -1)
			built_in_cd_error(d, pathname);
		else
			update_env_pwd(d, path_complete, pwd);
		double_free(path_slash, path_complete);
	}
	free(pwd);
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

void	update_env_pwd(t_exec_data *d, char *pathname, char *old_pwd)
{
	char	*new_pwd;
	char	*tmp_pwd;

	new_pwd = ft_strjoin("PWD=", pathname);
	add_var_to_env(&d->env, new_pwd);
	tmp_pwd = ft_strjoin("OLDPWD=", old_pwd);
	add_var_to_env(&d->env, tmp_pwd);
	free (new_pwd);
	free (tmp_pwd);
	return ;
}

char	*obtain_pwd(t_exec_data *d)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		d->int_error_code = ERROR_B_PWD;
		ft_error_handler(NULL, d);
		return (NULL);
	}
	return(ft_strdup(pwd));
}
