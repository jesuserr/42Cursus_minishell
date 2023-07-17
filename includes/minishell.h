/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:51:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 21:07:10 by cescanue         ###   ########.fr       */
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
# include <fcntl.h>

# define PROMPT "💾:>"
# define STARTMSG "Minishell Project by Jesus Serrano & Carlos Escañuela\n"

# define ERROR_XXX			(int)0
# define ERROR_CMDNOT		(int)1
# define ERROR_NOFILE		(int)2
# define ERROR_NOPERM		(int)13
# define ERROR_DUP			(int)253
# define ERROR_MALLOC		(int)254
# define ERROR_FORK			(int)255

# define T_PIPE				(int) 1
# define T_SEMICOLON		(int) 2
# define T_AND				(int) 3
# define T_OR				(int) 4

# define MAX_FDS 4096
# define BUFFER_SIZE 1024

typedef struct s_global_data
{
	char	**env;
}	t_global_data;

typedef struct s_exec_data
{
	int		fd_in;
	int		fd_out;
	int		saved_fd_in;
	int		saved_fd_out;
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
	int		type;
	char	*cmd;
	int		cmdin;
	int		cmdout;
	char	**heredoc;
	int		n_heredoc;
	char	**in_literal;
	int		n_in_literal;
	char	**in;
	int		n_in;
	char	**out;
	int		n_out;
	char	**out_add;
	int		n_out_add;
	int		*fd_to_close;
}	t_token;

t_global_data	g_data;

int		ft_heredoc(char *sep);
char	*get_next_line(int fd);
void	ft_executor(t_list **lst_cmds);
void	ft_executor_heredoc(t_list *lst);
void	ft_executor_in_literal(t_list *lst);
int		ft_executor_in_file(t_list *lst);
int		ft_executor_out_file(t_list *lst);
int		ft_executor_out_file_add(t_list *lst);
void	ft_executor_close_fds(t_token *t);
void	ft_executor_add_fd(int fd, t_token *t);
void	ft_executor_cmds(t_list *lst);
void	p_t_s_free_token(void *t);
t_list	**parser(char *line);
int		p_common_errors(char *line);
char	*p_identify_blocks(char *line);
char	*p_replace_env(char	*tline);
char	*p_strnstr(const char *haystack, const char *needle, size_t len);
char	*p2_strnstr(const char *haystack, const char *needle, size_t len);
t_token	*p_t_s(char *block);
int		p_t_s_count(char *block);
void	p_t_s_cmd(char *block, char **cmd);
int		p_t_s_type(char *block);
void	p_t_s_pattern(char *block, char *pattern, int *token_n, char ***t_str);
int		p_common_errors(char *line);
void	ft_error(char *error);
void	ft_error_shell(char *error);
int		ft_command_exec(t_exec_data *d);
void	ft_error_handler(char *str, t_exec_data *d);
char	**free_split(char **str_1, char *str_2);
char	**copy_dbl_char_pointer(char **src);
int		built_in_exec(t_exec_data *d);
int		exec_dups(t_exec_data *d);
int		restore_fds(t_exec_data *d);

#endif