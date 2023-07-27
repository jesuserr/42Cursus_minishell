/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:58:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/27 21:55:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(t_global *gd)
{
	char	*line;

	line = 0;
	while (ft_strncmp(line, "exit", ft_strlen(line)) != 0)
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		if (line && *line && ft_strncmp(line, "exit", ft_strlen(line)) != 0)
		{
			add_history(line);
			ft_executor(parser(line, gd), gd);
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
	t_global	gd;
	(void) argv;
	(void) argc;

	gd.env = ft_calloc(1, sizeof(char ***));
	*gd.env = copy_dbl_char_pointer(env);
	/*gd.int_error_code = 0;
	gd.term_status = 0;
	if (!gd.env)
	{
		gd.int_error_code = ERROR_MALLOC;
		ft_error_handler(NULL, &gd);
		return (-2);
	}*/
	/*
	if (argc == 2)
	{
		gd.int_error_code = 0;
		gd.term_status = 0;
		gd.fd_in = -1;
		gd.fd_out = -1;
		//d.fd_in = ft_heredoc("dd");
		//d.fd_in = open("input", O_RDONLY, 0444);
		//d.fd_out = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//del_var_from_env(&d.env, "HOME");
		gd.exec_args = ft_split_quotes("echo -n \\\\hola amigos", ' ');
		ft_printf(1, "Return:%d\t", built_in_echo(&gd));
		ft_printf(1, "Int.Error:%d\tTerm.Status:%d\n", gd.int_error_code, gd.term_status);
		//built_in_pwd(&d);
		//free_split(d.exec_args, NULL);
		//d.exec_args = ft_split("ls", ' ');
		//ft_command_exec(&d);
		free_split(gd.exec_args, NULL);
		gd.exec_args = ft_split("ls", ' ');
		ft_command_exec_cmd(&gd);		
		free_split(gd.env, NULL);
	}
	else*/
	{
		ft_startmsg();
		ft_readcmdline(&gd);
		free_split(*gd.env, 0);
		free(gd.env);

	}
	return (0);
}
