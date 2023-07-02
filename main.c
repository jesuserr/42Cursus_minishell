/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 10:58:10 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/02 11:49:43 by jesuserr         ###   ########.fr       */
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

void	child_process(int fd[2], char **argv, char **envp)
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

void	parent_process(int fd[2], char **argv, char **envp)
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
	pid_t	pid;

	printf("%s\n", readline("test> "));
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error_handler(ERROR_XXX, NULL);
		pid = fork();
		if (pid == -1)
			ft_error_handler(ERROR_XXX, NULL);
		if (pid == 0)
			child_process(fd, argv, envp);
		parent_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
	}
	else
		ft_error_handler(ERROR_ARGS, NULL);
}
