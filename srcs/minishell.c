/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/06 21:56:56 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(void)
{
	char	*line;

	line = readline(PROMPT);
	while (ft_strncmp(line, "exit", 4))
	{
		if (line)
		{
			if (*line)
				add_history(line);
			free(line);
		}
		line = readline(PROMPT);
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
	t_basic_data d;

	d.argc = argc;
	d.argv = argv;
	d.env = env;
	ft_startmsg();
	ft_readcmdline();
	return (0);
}
