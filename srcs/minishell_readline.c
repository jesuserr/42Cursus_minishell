/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:18:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/07 01:10:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		//line = readline(" ");
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
