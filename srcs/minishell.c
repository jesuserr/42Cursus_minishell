/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 22:02:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(void)
{
	char	*line;
	t_list	**list_cmds;
	t_list	*lst;
	
	line = 0;
	while (!line || ft_strncmp(line, "exit", 4))
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		if (line && *line)
		{
			add_history(line);
			list_cmds = parser(line);
			//para revisar -- Esto es una prueba de si la lista se crear
			//revisar tema pendientes de las variables de entorno, se tienen que expàindir, incluso si estan pegadas a mas texto, se diferencia por que estan en mayusculas
			lst = *list_cmds;
			while(lst)
			{
				printf("type:%s\n", ((t_token *)lst->content)->cmd);
				lst = lst->next;
			}
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
