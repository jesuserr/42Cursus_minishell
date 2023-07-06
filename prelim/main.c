/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:58:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/06 21:39:46 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	char	*temp;

	args = ft_split(cmd, ' ');
	path = obtain_path(args[0], envp);
	if (!path)
	{
		temp = ft_strdup(args[0]);
		free_split(args);
		ft_error_handler(ERROR_CMD, temp);
	}
	if (execve(path, args, envp) == -1)
		ft_error_handler(ERROR_XXX, NULL);
}

void	child_process_1(int fd[2], char **argv, char **envp)
{
	int	file;

	file = open(argv[1], O_RDONLY, 0444);
	if (file == -1)
		ft_error_handler(ERROR_FILE, argv[1]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error_handler(ERROR_XXX, NULL);
	if (dup2(file, STDIN_FILENO) == -1)
		ft_error_handler(ERROR_XXX, NULL);
	close(file);
	close(fd[1]);
	close(fd[0]);
	execute(argv[2], envp);
}

void	child_process_2(int fd[2], char **argv, char **envp)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		ft_error_handler(ERROR_XXX, NULL);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error_handler(ERROR_XXX, NULL);
	if (dup2(file, STDOUT_FILENO) == -1)
		ft_error_handler(ERROR_XXX, NULL);
	close(file);
	close(fd[1]);
	close(fd[0]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error_handler(ERROR_XXX, NULL);
		pid[0] = fork();
		if (pid[0] == -1)
			ft_error_handler(ERROR_XXX, NULL);
		if (pid[0] == 0)
			child_process_1(fd, argv, envp);
		pid[1] = fork();
		if (pid[1] == -1)
			ft_error_handler(ERROR_XXX, NULL);
		if (pid[1] == 0)
			child_process_2(fd, argv, envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], NULL, 0);
	}
	else
		ft_error_handler(ERROR_ARGS, NULL);
}
