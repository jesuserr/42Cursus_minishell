/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/10 13:05:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/* Checks if input contains '/' what means that path has been provided by */
/* user, othervise returns NULL to search path with 'check_env_path' */
/* If path provided is correct returns same path, if not returns NULL and */
/* handles the error */
char	*check_usr_path(t_basic_data *d)
{
	char	**args;
	char	*path;

	args = ft_split(d->argv[1], ' ');			// d->argv[1] is temporal
	if (ft_strchr(args[0], '/') != NULL)
	{
		if (!(access(args[0], F_OK | X_OK) == 0))
		{
			d->int_error_code = ERROR_NOFILE;
			d->term_status = 127;
			ft_error_handler(args[0], d);
		}
		else
		{
			path = ft_strdup(args[0]);
			free_split(args, NULL);
			return (path);
		}
	}
	free_split(args, NULL);
	return (NULL);
}

/* If no path has been found returns NULL and handles the error */
/* If path is correct returns path */
char	*check_env_path(t_basic_data *d)
{
	char	**args;
	char	*path;

	args = ft_split(d->argv[1], ' ');			// d->argv[1] is temporal
	path = obtain_path(args[0]);
	if (!path)
	{
		d->int_error_code = ERROR_CMD;
		d->term_status = 127;
		ft_error_handler(args[0], d);
		free_split(args, NULL);
		return (NULL);
	}
	free_split(args, NULL);
	return (path);
}

/* Main execution function, checks path/command received and if correct */
/* creates child process for its execution */
/* Returns error codes (0) OK, (-1) command/path error, (-2) system error */
/* Provides error info inside struct variables int_error_code & term.status */
int	ft_command_exec(t_basic_data *d)
{
	char	**args;
	char	*path;	

	path = check_usr_path(d);
	if (!path && d->term_status == 127)
		return (-1);
	if (!path)
		path = check_env_path(d);
	if (!path && d->term_status == 127)
		return (-1);
	args = ft_split(d->argv[1], ' ');			// d->argv[1] is temporal
	d->fork_pid = fork();
	if (d->fork_pid == -1)
	{
		free_split(args, path);
		d->int_error_code = ERROR_XXX;			// how to handle sys errors?
		ft_error_handler(NULL, d);
		return (-2);
	}
	if (d->fork_pid == 0)
		execve(path, args, d->env);
	waitpid(d->fork_pid, &d->waitpid_status, 0);
	d->term_status = WEXITSTATUS(d->waitpid_status);
	free_split(args, path);
	return (0);
}
