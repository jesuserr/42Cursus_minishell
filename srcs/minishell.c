/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 13:21:23 by jesuserr         ###   ########.fr       */
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
		d.env = copy_dbl_char_pointer(env);
		if (!d.env)
		{
			d.int_error_code = ERROR_MALLOC;
			ft_error_handler(NULL, &d);
			return (-2);
		}
		d.int_error_code = 0;
		d.term_status = 0;
		d.exec_path = NULL;
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
