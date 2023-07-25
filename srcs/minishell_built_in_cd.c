/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:16 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:17 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in_cd_error(t_exec_data *d, char *pathname);
int		execute_cd_home(t_exec_data *d);
int		execute_cd_absolute(t_exec_data *d, char *new_pwd);
int		execute_cd_relative(t_exec_data *d, char *new_pwd);

int	built_in_cd(t_exec_data *d, char *pathname)
{
	char	*new_pwd;
	char	*pwd;

	if (pathname[0] == '.' && pathname[1] == '\0')
		return (0);
	if (check_empty_string(pathname))
		return (execute_cd_home(d));
	if (pathname[0] == '/')
		return (execute_cd_absolute(d, pathname));
	if (!(ft_strncmp(pathname, "..", 2)) && ft_strlen(pathname) == 2)
	{
		pwd = obtain_pwd(d);
		if (!pwd)
			return (-1);
		chdir(pathname);
		new_pwd = obtain_pwd(d);
		update_env_pwd(d, new_pwd, pwd);
		double_free(new_pwd, pwd);
	}
	else
		return (execute_cd_relative(d, pathname));
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

int	execute_cd_home(t_exec_data *d)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = obtain_pwd(d);
	if (!old_pwd)
		return (-1);
	new_pwd = get_env_var(d, "HOME");
	if (!new_pwd)
	{
		free(old_pwd);
		return (0);
	}
	chdir(new_pwd);
	update_env_pwd(d, new_pwd, old_pwd);
	double_free(old_pwd, new_pwd);
	return (0);
}

int	execute_cd_absolute(t_exec_data *d, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = obtain_pwd(d);
	if (!old_pwd)
		return (-1);
	if (chdir(new_pwd) == -1)
		built_in_cd_error(d, new_pwd);
	else
		update_env_pwd(d, new_pwd, old_pwd);
	free(old_pwd);
	return (0);
}

int	execute_cd_relative(t_exec_data *d, char *new_pwd)
{
	char	*path_complete;
	char	*path_slash;
	char	*old_pwd;

	old_pwd = obtain_pwd(d);
	if (!old_pwd)
		return (-1);
	path_slash = ft_strjoin(old_pwd, "/");
	path_complete = ft_strjoin(path_slash, new_pwd);
	if (chdir(new_pwd) == -1)
		built_in_cd_error(d, new_pwd);
	else
		update_env_pwd(d, path_complete, old_pwd);
	double_free(path_slash, path_complete);
	free(old_pwd);
	return (0);
}
