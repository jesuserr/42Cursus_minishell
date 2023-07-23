/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/22 20:56:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

#define READ_END 0
#define WRITE_END 1

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	char **als;
	char **acat;
	char **awc;
	char tls[] = "/bin/ls -la";
	char tcat[] = "/bin/cat";
	char twc[] = "/usr/bin/wc -l";
	als = ft_split(tls, ' ');
	acat = ft_split(tcat, ' ');
	awc = ft_split(twc, ' ');
	int fd1[2];
	int fd2[2];
	pid_t	pid;
	
	(void) als;
	(void) acat;
		
	pipe(fd1);

	pid = fork();

	if (!pid)
	{ 	
		close(fd1[READ_END]);
		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);
		execve(acat[0], acat, env);
	}
	else
	{
		close(fd1[WRITE_END]);

		pipe(fd2);
		pid = fork();
		if (!pid)
		{
			close (fd2[READ_END]);
			dup2(fd1[READ_END], STDIN_FILENO);
			close(fd1[READ_END]);
			dup2(fd2[WRITE_END], STDOUT_FILENO);
			close(fd2[WRITE_END]);
			execve(als[0], als, env);
		}
		else
		{
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);
			pid = fork();
			if (!pid)
			{
				dup2(fd2[READ_END], STDIN_FILENO);
				close(fd2[READ_END]);
				execve(awc[0], awc, env);
			}
			
		}
	}
	close(fd2[READ_END]);
	wait(0);
	wait(0);
	wait(0);
}
