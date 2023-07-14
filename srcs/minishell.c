/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/14 21:23:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(char **env)
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
			lst = *list_cmds;
			while(lst)
			{
				t_exec_data *t_exec;
				t_token *t;
				t_exec = ft_calloc(1, sizeof(t_exec_data));
				t = ((t_token *)lst->content);
				t_exec->exec_args = ft_split(t->cmd, ' ');
				t_exec->argv = 0;
				t_exec->env = copy_dbl_char_pointer(env);
				t_exec->int_error_code = 0;
				t_exec->term_status = 0;
				t_exec->exec_path = NULL;
				ft_command_exec(t_exec);
				free_split(t_exec->env, NULL);
				free(t_exec);
				lst = lst->next;
			}
			ft_lstclear(list_cmds, p_t_s_free_token);
			free(*list_cmds);
			free(list_cmds);
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
		built_in_exec(&d);
		//printf("Return:%d\t", ft_command_exec(&d));
		printf("Int.Error:%d\tTerm.Status:%d\n", d.int_error_code, d.term_status);
		free_split(d.env, NULL);
	}
	else
	{
		ft_startmsg();
		ft_readcmdline(env);
	}
	return (0);
}
