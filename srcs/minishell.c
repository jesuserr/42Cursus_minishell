/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/14 10:27:25 by cescanue         ###   ########.fr       */
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
		if (line && *line && ft_strncmp(line, "exit", 4) != 0)
		{
			add_history(line);
			list_cmds = parser(line);
			//para revisar -- Esto es una prueba de si la lista se crear
			//Tengo un leak de memoria con cadenas complejas like : RM_CMD="$(rm -rf 'ls -t ${FOLDER}/other_folder | awk NR>5')", revisar
			lst = *list_cmds;
			while(lst)
			{
				t_token *t;
				t = ((t_token *)lst->content);
				printf("type:%s\n", t[0].cmd);
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
