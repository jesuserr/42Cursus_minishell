/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:18:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/10 16:48:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_checkexitargv1(char **tline, int *args, int *args2)
{
	char	deli;

	while (*tline && **tline)
	{
		if (**tline == '\'' || **tline == '\"')
		{
			deli = **tline;
			(*tline)++;
			while (**tline && **tline != deli)
				(*tline)++;
		}
		if (**tline == ' ')
		{
			(*args)++;
			(*args2)++;
		}
		(*tline)++;
	}
}

char	*ft_checkexitargv(char *line)
{
	char	*tline;
	int		args;
	int		args2;

	tline = line;
	args = 0;
	args2 = 0;
	if (!ft_strncmp(tline, "exit", 4))
	{
		tline += 5;
		while (tline && *tline && *tline == ' ')
			tline++;
		ft_checkexitargv1(&tline, &args, &args2);
		if (args && args2 && ft_isdigit(line[5]))
		{
			free(line);
			ft_error_shell("exit: too many arguments");
			g_info->last_status = 1;
			return (0);
		}
	}
	return (line);
}

char	*ft_readcmdline2(char *line, t_global *gd)
{
	int		status_h;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	free (line);
	line = tmp;
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
	line = ft_checkexitargv(line);
	if (line && *line && ft_strncmp(line, "exit", 4) != 0)
	{
		if (status_h == 1)
			add_history(line);
		ft_executor(parser(line, gd), gd);
	}
	return (line);
}

char	*ft_readcmdline(t_global *gd)
{
	char	*line;
	char	*pwd;

	line = 0;
	while (ft_strncmp(line, "exit", 4) != 0)
	{
		if (line)
			free(line);
		pwd = pwd_as_prompt();
		line = readline(pwd);
		free (pwd);
		if (line)
			line = ft_readcmdline2(line, gd);
		else if (!line)
		{
			ft_printf(1, "\b%sexit\n", PROMPT);
			line = ft_strdup("exit");
		}
	}
	return (line);
}
