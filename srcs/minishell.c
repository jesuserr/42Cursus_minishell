/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:58:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/08/02 20:24:45 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_readcmdline2(char *line, t_global *gd)
{
	int	status_h;

	if (!line)
	{
		ft_printf(1, "\b%sexit\n", PROMPT);
		line = ft_strdup("exit");
	}
	if (line && *line)
	{
		status_h = ft_check_history(line);
		if (status_h == 2)
			line = ft_history(line);
		if (status_h == 0)
		{
			free (line);
			line = 0;
		}
	}
	if (line && *line && ft_strncmp(line, "exit", 4) != 0)
	{
		if (status_h == 1)
			add_history(line);
		ft_executor(parser(line, gd), gd);
	}
	return (line);
}

void	ft_readcmdline(t_global *gd)
{
	char	*line;

	line = 0;
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		line = ft_readcmdline2(line, gd);
	}
	if (line)
	{
		free(line);
		line = 0;
	}
}

void	ft_startmsg(void)
{
	ft_printf(STDOUT_FILENO, "%s", STARTMSG);
}

void	ft_init_gd(t_global *gd, char **env)
{
	g_info = gd;
	gd->env = ft_calloc(1, sizeof(char ***));
	*gd->env = copy_dbl_char_pointer(env);
	gd->cmds = ft_calloc(1, sizeof(t_list ***));
	*gd->cmds = 0;
	if (!gd->env || !(*gd->env))
	{
		ft_printf(STDERR_FILENO, "minishell: malloc: Cannot allocate memory\n");
		exit(EXIT_FAILURE);
	}
	gd->last_status = 0;
	gd->copy_stdin = dup(STDIN_FILENO);
	gd->copy_stdout = dup(STDOUT_FILENO);
	if (gd->copy_stdin == -1 || gd->copy_stdout == -1)
	{
		ft_printf(STDERR_FILENO, "minishell: dup: Cannot copy std in | out\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_global	gd;

	(void) argv;
	(void) argc;
	ft_init_gd(&gd, env);
	ft_signals_init();
	ft_startmsg();
	ft_readcmdline(&gd);
	free_split(*gd.env, 0);
	free(gd.env);
	free(gd.cmds);
	return (0);
}
