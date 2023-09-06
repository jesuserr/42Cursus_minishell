/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:58:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 08:01:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_get_exitcode(char *line)
{
	int	count;

	count = 4;
	if (ft_strlen(line) > 4)
	{
		while (line[count] && (line[count] == ' ' || line[count] == '('))
			count++;
		return (ft_atoi(&line[count]));
	}
	else
		return (g_info->last_status);
}

int	main(int argc, char **argv, char **env)
{
	t_global	gd;
	int			exitcode;
	char		*line;

	(void) argv;
	(void) argc;
	ft_init_gd(&gd, env);
	ft_signals_init();
	//ft_startmsg();
	line = ft_readcmdline(&gd);
	exitcode = ft_get_exitcode(line);
	free_split(*gd.env, line);
	free(gd.env);
	free(gd.cmds);
	return (exitcode);
}
