/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:30 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/12 21:18:06 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../ft_printf/libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include "errno.h"

# define PROMPT "💾:>"
# define STARTMSG "Minishell Project by Jesus Serrano & Carlos Escañuela\n"

# define ERROR_XXX		(int)0
# define ERROR_CMDNOT	(int)1
# define ERROR_NOFILE	(int)2
# define ERROR_NOPERM	(int)13
# define ERROR_FORK		(int)255

typedef struct s_exec_data
{
	int		fdin;
	int		fdout;	
	char	**argv;
	char	**env;
	int		int_error_code;
	int		term_status;
	int		waitpid_status;
	pid_t	fork_pid;
	char	**exec_args;
	char	*exec_path;
}	t_exec_data;

typedef struct s_token
{
	char	**heredoc;
	char	**in;
	char	**out;
	int		outtype;
}	t_token;

void	parser(char *line);
char	*p_identify_blocks(char *line);
char	*p_replace_env(char	*tline);
char	*p_strnstr(const char *haystack, const char *needle, size_t len);
void	p_t_s(char *block);
int		p_common_errors(char *line);
void	ft_error(char *error);
void	ft_error_shell(char *error);
int		ft_command_exec(t_exec_data *d);
void	ft_error_handler(char *str, t_exec_data *d);
void	free_split(char **str_1, char *str_2);

#endif