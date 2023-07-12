/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/12 21:14:53 by cescanue         ###   ########.fr       */
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
	t_exec_data	d;

	if (argc == 2)
	{
		d.argv = argv;
		d.env = env;
		d.int_error_code = 0;
		d.term_status = 0;
		d.exec_path = NULL;
		printf("Return:%d\t", ft_command_exec(&d));
		printf("Int.Error:%d\tTerm.Status:%d\n", d.int_error_code, d.term_status);
	}
	else
	{
		ft_startmsg();
		ft_readcmdline();
	}
	return (0);
}
