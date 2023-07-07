/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/07 21:29:54 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(void)
{
	char	*line;

	line = 0;
	while (!line || ft_strncmp(line, "exit", 4))
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		if (line && *line)
		{
			add_history(line);
			parser(line);
		}
	}
	if (line)
		free(line);
}

void	ft_startmsg(void)
{
	ft_printf(STARTMSG);
}

int	main(int argc, char **argv, char **env)
{
	t_basic_data	d;

	d.argc = argc;
	d.argv = argv;
	d.env = env;
	ft_startmsg();
	ft_readcmdline();
	return (0);
}
