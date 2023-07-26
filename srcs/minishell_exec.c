/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/26 19:11:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Checks if input contains '/' what means that path has been provided by */
/* user, othervise returns NULL to search path with 'obtain_path'. */
/* Checks the existence and also the execution rights for the command, */
/* if everything is correct returns same path otherwise returns NULL and */
/* error information */
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
			ft_error_handler(NULL, d);
		}
		else
			return (ft_strdup(d->exec_args[0]));
	}
	return (NULL);
}

/* Verifies existence and execution rights for all paths contained in PATH */
/* Returns 1 if success, otherwise returns 0 and error information */
int	check_access(char *path, t_exec_data *d)
{
	d->int_error_code = 0;
	d->term_status = 0;
	if (access(path, F_OK))
	{
		d->int_error_code = ERROR_CMDNOT;
		d->term_status = 127;
	}
	else if (access(path, X_OK))
	{
		d->int_error_code = ERROR_NOPERM;
		d->term_status = 126;
	}
	else
		return (1);
	return (0);
}

/* Checks all paths in PATH and returns the one that contains the command */
/* Path returned contains path + command, otherwise returns NULL path */
char	*obtain_path(t_exec_data *d)
{
	char	**all_paths;
	char	*path;
	char	*temp_path;
	int		i;

	i = 0;
	while (ft_strnstr(d->env[i], "PATH=", 5) == NULL)
		i++;
	all_paths = ft_split(d->env[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_strjoin(all_paths[i++], "/");
		path = ft_strjoin(temp_path, d->exec_args[0]);
		free(temp_path);
		if (check_access(path, d))
		{
			free_split(all_paths, NULL);
			return (path);
		}
		free(path);
	}
	free_split(all_paths, NULL);
	return (NULL);
}

/* Opens a child process to execute the command once we are sure that exists */
/* and that the user has execution rights */
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
	{
		ft_exec_pipe_child(d);
		execve(d->exec_path, d->exec_args, d->env);
	}
	else
	{
		free_split(d->exec_args, d->exec_path);
		ft_exec_pipe_parent(d);
	}
	return (0);
}

/* Main execution function, checks path/command received and if correct */
/* creates child process for its execution */
/* Returns error codes (0) OK, (-1) command/path error, (-2) system error */
/* Provides error info inside struct variables int_error_code & term.status */
int	ft_command_exec(t_exec_data *d)
{
	if (check_empty_string(d->exec_args[0]) == -1)
		return (-1);
	d->exec_path = check_usr_path(d);
	if (!d->exec_path && d->term_status)
	{
		free_split(d->exec_args, NULL);
		return (-1);
	}
	if (!d->exec_path)
		d->exec_path = obtain_path(d);
	if (!d->exec_path)
	{
		ft_error_handler(NULL, d);
		free_split(d->exec_args, NULL);
		return (-1);
	}
	return (exec_fork(d));
}
