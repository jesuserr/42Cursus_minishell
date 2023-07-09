/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:30 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/09 21:26:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../ft_printf/libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define PROMPT "💾:>"
# define STARTMSG "Minishell Project by Jesus Serrano & Carlos Escañuela\n"

# define ERROR_XXX		0
# define ERROR_CMD		1

typedef struct s_basic_data
{
	int		fdin;
	int		fdout;
	int		argc;
	char	**argv;
	char	**env;
}	t_basic_data;

void	parser(char *line);
char	*p_identify_blocks(char *line);
char	*p_replace_env(char	*tline);
int		p_common_errors(char *line);
void	ft_error(char *error);
void	ft_error_shell(char *error);
int		ft_command_exec(t_basic_data *d);
void	ft_error_handler(int error, char *str);

#endif