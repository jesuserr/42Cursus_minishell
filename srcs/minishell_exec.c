/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/12 19:17:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Checks if input contains '/' what means that path has been provided by */
/* user, othervise returns NULL to search path with 'check_env_path' */
/* If path provided is correct returns same path, if not returns NULL and */
/* handles the error */
char	*check_usr_path(t_exec_data *d)
{
	if (ft_strchr(d->exec_args[0], '/') != NULL)
	{
		if (access(d->exec_args[0], F_OK))
		{
			d->int_error_code = ERROR_NOFILE;
			d->term_status = 127;
			ft_error_handler(d->exec_args[0], d);
		}
		else if (access(d->exec_args[0], X_OK))
		{
			d->int_error_code = ERROR_NOPERM;
			d->term_status = 126;
			ft_error_handler(d->exec_args[0], d);
		}
		else
			return (ft_strdup(d->exec_args[0]));
	}
	return (NULL);
}

/* Checks all paths in PATH and returns the one that contains the command */
/* Path returned contains path + command, otherwise returns NULL path */
char	*obtain_path(char *cmd)
{
	char	**all_paths;
	char	*path;
	char	*temp_path;
	int		i;

	all_paths = ft_split(getenv("PATH="), ':');
	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(all_paths, NULL);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(all_paths, NULL);
	return (NULL);
}

/* If no path has been found returns NULL and handles the error */
/* If path is correct returns path */
char	*check_env_path(t_exec_data *d)
{
	d->exec_path = obtain_path(d->exec_args[0]);
	if (!d->exec_path)
	{
		d->int_error_code = ERROR_CMDNOT;
		d->term_status = 127;
		ft_error_handler(d->exec_args[0], d);
		return (NULL);
	}
	return (d->exec_path);
}

int	exec_fork(t_exec_data *d)
{
	d->fork_pid = fork();
	if (d->fork_pid == -1)
	{
		d->int_error_code = ERROR_FORK;
		ft_error_handler(NULL, d);
		free_split(d->exec_args, d->exec_path);
		return (-2);
	}
	if (d->fork_pid == 0)
		execve(d->exec_path, d->exec_args, d->env);
	waitpid(d->fork_pid, &d->waitpid_status, 0);
	d->term_status = WEXITSTATUS(d->waitpid_status);
	free_split(d->exec_args, d->exec_path);
	if (d->term_status)
		return (-1);
	return (0);
}

/* Main execution function, checks path/command received and if correct */
/* creates child process for its execution */
/* Returns error codes (0) OK, (-1) command/path error, (-2) system error */
/* Provides error info inside struct variables int_error_code & term.status */
int	ft_command_exec(t_exec_data *d)
{
	d->exec_args = ft_split(d->argv[1], ' ');
	d->exec_path = check_usr_path(d);
	if (!d->exec_path && d->term_status)
	{
		free_split(d->exec_args, NULL);
		return (-1);
	}
	if (!d->exec_path)
		d->exec_path = check_env_path(d);
	if (!d->exec_path)
	{
		free_split(d->exec_args, NULL);
		return (-1);
	}
	return (exec_fork(d));
}
