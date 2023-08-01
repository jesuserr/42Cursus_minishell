/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:12:47 by cescanue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/01 12:52:53 by cescanue         ###   ########.fr       */
=======
/*   Updated: 2023/08/01 13:17:13 by jesuserr         ###   ########.fr       */
>>>>>>> 9faca01e309fc073ae1c5a4183504ef47d4e5ae3
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
# include <limits.h>
# include <signal.h>

# define PROMPT "💾:>"
# define STARTMSG "Minishell Project by Jesus Serrano & Carlos Escañuela\n"

# define ERROR_XXX			0
# define ERROR_CMDNOT		1
# define ERROR_NOFILE		2
# define ERROR_NOPERM		13
# define ERROR_NODIR		20
# define ERROR_B_PWD		200
# define ERROR_B_UNSET		201
# define ERROR_B_NOHOME		202
# define ERROR_B_EXPORT		203
# define ERROR_B_TOKEN_D	204
# define ERROR_B_TOKEN_S	205
# define ERROR_DUP			253
# define ERROR_MALLOC		254
# define ERROR_FORK			255

# define T_PIPE				1
# define T_SEMICOLON		2
# define T_AND				3
# define T_OR				4

# define MAX_FDS 			4096
# define BUFFER_SIZE 		1024

# define READ_END			0
# define WRITE_END			1

typedef struct s_global
{
	char				***env;
	int					last_status;
	t_list				***cmds;
	int					copy_stdin;
	int					copy_stdout;
}	t_global;

typedef struct s_exec_data
{
	int		fd_in;
	int		fd_out;
	int		pipe_current[2];
	int		pipe_last[2];
	int		n_in;
	int		n_out;
	int		redi_in;
	int		redi_out;
	int		saved_fd_in;
	int		saved_fd_out;
	char	***env;
	int		int_error_code;
	int		term_status;
	int		waitpid_status;
	pid_t	fork_pid;
	int		fork_pid_status;
	char	**exec_args;
	char	*exec_path;
}	t_exec_data;

typedef struct s_token
{
	int			type;
	char		*cmd;
	int			cmdin;
	int			cmdout;
	char		**heredoc;
	int			n_heredoc;
	char		**in_literal;
	int			n_in_literal;
	char		**in;
	int			n_in;
	char		**out;
	int			n_out;
	char		**out_add;
	int			n_out_add;
	int			*fd_to_close;
	int			last_in;
	int			last_out;
	t_exec_data	*d;
}	t_token;

t_global	*g_info;

int		ft_close_pipe(int pipe);
int		ft_heredoc(char *sep);
char	*get_next_line(int fd);
void	ft_executor(t_list ***lst_cmds, t_global *gd);
void	ft_executor_heredoc(t_token *token);
void	ft_executor_in_literal(t_token *token);
int		ft_executor_in_file(t_token *token);
int		ft_executor_out_file(t_token *t);
int		ft_executor_out_file_add(t_token *t);
void	ft_executor_close_fds(t_token *t);
void	ft_executor_add_fd(int fd, t_token *t);
void	ft_executor_cmds(t_list *lst, t_global *gd);
int		ft_executor_check_cmds(t_list *lst, t_global *gd);
int		ft_executor_check_built_in(t_exec_data	*d);
void	ft_exec_pipe_child(t_exec_data *d);
void	ft_exec_pipe_parent(t_exec_data *d);
void	ft_exec_built_in_pipe_start(t_exec_data *d);
void	ft_exec_built_in_pipe_end(t_exec_data *d);
void	p_t_s_free_token(void *t);
t_list	***parser(char *line, t_global *gd);
int		p_common_errors(char *line);
char	*p_identify_blocks(char *line);
char	*p_replace_env(char	*tline, t_global *gd);
char	*p_strnstr(const char *haystack, const char *needle, size_t len);
char	*p2_strnstr(const char *haystack, const char *needle, size_t len);
t_token	*p_t_s(char *block);
int		p_t_s_count(char *block);
void	p_t_s_cmd(char *block, char **cmd);
int		p_t_s_type(char *block);
void	p_t_s_pattern(char *block, char *pattern, int *token_n, char ***t_str);
int		p_common_errors(char *line);
int		ft_command_exec_built_in(t_exec_data *d);
void	ft_strtolower(char *str);
int		built_in_history(t_exec_data *d);
void	ft_signals_init(void);
/*	minishell_exec_cmd.c	*/
int		ft_command_exec_cmd(t_exec_data *d);
char	*check_usr_path(t_exec_data *d);
char	*obtain_path(t_exec_data *d);
/*	minishell_error.c	*/
void	ft_error(char *error);
void	ft_error_shell(char *error);
void	ft_error_handler(char *str, t_exec_data *d);
/*	minishell_utils.c	*/
char	**free_split(char **str_1, char *str_2);
char	**copy_dbl_char_pointer(char **src);
int		check_empty_string(char *str);
int		count_dbl_char_lines(char **env);
void	double_free(char *str_1, char *str_2);
/*	minishell_utils_2.c	*/
void	swap_values(int *a, int *b);
/*	minishell_built_ins.c */
int		built_in_pwd(t_exec_data *d);
int		built_in_env(t_exec_data *d);
int		built_in_unset(t_exec_data *d);
/*	minishell_built_ins_utils.c */
char	*obtain_pwd(t_exec_data *d);
void	init_array(int **array, int env_l);
int		longest_var(t_exec_data *d);
void	export_var_error(t_exec_data *d, int j, int *flag);
/*	minishell_built_in_cd.c	*/
int		built_in_cd(t_exec_data *d);
/*	minishell_built_in_export	*/
int		built_in_export(t_exec_data *d);
/*	minishell_built_in_echo.c */
int		built_in_echo(t_exec_data *d);
char	*quotes_analysis(char *str);
int		verify_syntax_quotes(char *str);
/*	minishell_exec_fds.c	*/
int		exec_dups(t_exec_data *d);
int		restore_fds(t_exec_data *d);
/*	minishell_split_with_quotes.c	*/
char	**ft_split_quotes(char const *s, char c);
void	ft_strtrim_quotes(char **strs);
/*	minishell_env_utils.c	*/
char	*get_env_var(t_exec_data *d, char *name);
char	**add_var_to_env(char ***src, char *line);
char	**del_var_from_env(char ***src, char *line);

#endif