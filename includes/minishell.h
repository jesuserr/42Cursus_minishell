/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:57:30 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/07 21:25:45 by cescanue         ###   ########.fr       */
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
void	p_common_errors(char *line);
void	ft_error(char *error);
int		exec(t_basic_data *d);

#endif