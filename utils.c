/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:57:51 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/02 10:57:52 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_handler(int error, char *str)
{
	if (error == ERROR_ARGS)
		ft_printf("%sError: Wrong arguments", RED);
	else if (error == ERROR_XXX)
		perror(RED"Error");
	else if (error == ERROR_FILE)
		fprintf (stderr, "pipex: %s: No such file or directory\n", str);
	else if (error == ERROR_CMD)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(str);
		exit(127);
	}
	exit(EXIT_FAILURE);
}

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*obtain_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
