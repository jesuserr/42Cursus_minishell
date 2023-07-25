/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/25 12:12:43 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_cd_error(t_exec_data *d, char *pathname);
void	update_env_pwd(t_exec_data *d, char *pathname, char *old_pwd);

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
	if (check_empty_string(pathname))
	{
		path_complete = get_env_var(d, "HOME");
		if (!path_complete)
		{
			free(pwd);
			return (0);
		}
		chdir(path_complete);
		update_env_pwd(d, path_complete, pwd);
		free(path_complete);
	}
	else if (pathname[0] == '/')
	{
		if (chdir(pathname) == -1)
			built_in_cd_error(d, pathname);
		else
			update_env_pwd(d, pathname, pwd);
	}
	else if (!(ft_strncmp(pathname, "..", 2)) && ft_strlen(pathname) == 2)
	{
		chdir(pathname);
		path_complete = obtain_pwd(d);
		update_env_pwd(d, path_complete, pwd);
		free(path_complete);
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

void	update_env_pwd(t_exec_data *d, char *new_path, char *old_path)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = ft_strjoin("PWD=", new_path);
	add_var_to_env(&d->env, new_pwd);
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	add_var_to_env(&d->env, old_pwd);
	free (new_pwd);
	free (old_pwd);
	return ;
}
