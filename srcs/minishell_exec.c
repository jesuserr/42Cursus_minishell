/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:15:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/08 21:41:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

// que pasa si no hay PATH?
char	*obtain_path(char *cmd, t_basic_data *d)
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
		temp_path = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_split(all_paths);
	return (NULL);
}

// si falla el execve tenemos un problema pues el child
// ha de comunicarse con el parent
// no encontré nadie que lo proteja correctamente
int	ft_command_exec(t_basic_data *d)
{
	char	**args;
	char	*path;
	char	*tmp;
	pid_t	pid;

	args = ft_split(d->argv[1], ' ');
	path = obtain_path(args[0], d);
	if (!path)
	{
		tmp = ft_strdup(args[0]);
		free_split(args);
		ft_error_handler(ERROR_CMD, tmp);
	}
	pid = fork();
	if (pid == -1)
		ft_error_handler(ERROR_XXX, NULL);
	if (pid == 0)
		execve(path, args, d->env);
	waitpid(pid, NULL, 0);
	free_split(args);
	free(path);
	return (0);
}
