/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/25 13:53:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline()
{
	char	*line;

	line = 0;
	while (!line || ft_strncmp(line, "exit", ft_strlen(line)))
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		if (line && *line && ft_strncmp(line, "exit", ft_strlen(line)) != 0)
		{
			add_history(line);
			ft_executor(parser(line));
		}
	}
	if (line)
		free(line);
}

void	ft_startmsg(void)
{
	printf(STARTMSG);
}

int	main(int argc, char **argv, char **env)
{
	t_exec_data	d;

	g_data.env = copy_dbl_char_pointer(env);
	if (!g_data.env)
	{
		d.int_error_code = ERROR_MALLOC;
		ft_error_handler(NULL, &d);
		return (-2);
	}

	if (argc == 2)
	{
		d.argv = argv;
		d.env = copy_dbl_char_pointer(env);
		if (!d.env)
		{
			d.int_error_code = ERROR_MALLOC;
			ft_error_handler(NULL, &d);
			return (-2);
		}
		d.int_error_code = 0;
		d.term_status = 0;
		d.fd_in = -1;
		d.fd_out = -1;
		//d.fd_in = ft_heredoc("dd");
		//d.fd_in = open("input", O_RDONLY, 0444);
		//d.fd_out = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//built_in_exec(&d);
		printf("Return:%d\t", ft_command_exec(&d));
		printf("Int.Error:%d\tTerm.Status:%d\n", d.int_error_code, d.term_status);
		free_split(d.env, NULL);
	}
	else
	{
		ft_startmsg();
		ft_readcmdline();
	}
	return (0);
}
