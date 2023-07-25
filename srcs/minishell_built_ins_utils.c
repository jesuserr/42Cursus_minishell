/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:09:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:35 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Returns path working directory using getcwd instead of our environment */
/* PWD variable to avoid failure in case that PWD is not present */
/* Returned value must be freed by the calling function */
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
	return (ft_strdup(pwd));
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
