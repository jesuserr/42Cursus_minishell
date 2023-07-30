/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_echo.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:12:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/31 00:09:18 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_print(t_exec_data *d, char *str);
int		verify_syntax(t_exec_data *d, char *str);

/*****************************************************************/
/* IMPORTANT!! ALL THE ARGS OF ECHO MUST BE IN JUST ONE ARGUMENT */
/* FUNCTION MUST BE MODIFIED WHEN THIS IS DONE 					 */
/*****************************************************************/
/* Prints out the list of arguments provided, if first argument is -n */
/* no newline is sent to terminal at the end of the printing */
/* No STDIN for this kind of built-in */
int	built_in_echo(t_exec_data *d)
{
	int	i;
	int	flag;

	if (!d->exec_args[1])
	{
		ft_printf(STDOUT_FILENO, "\n");
		return (0);
	}
	i = 1;
	flag = 0;
	if (!(ft_strncmp(d->exec_args[1], "-n", 2)) && \
	ft_strlen(d->exec_args[1]) == 2)
	{
		flag = 1;
		i++;
	}
	while (d->exec_args[i])
	{
		echo_print(d, d->exec_args[i++]);
		if (d->exec_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (!flag && d->term_status == 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}

/* Verifies if the single and double quotes sintax is correct */
/* If is correct prints out (character by character) the string */
/* following same quoting rules applied inside 'verify_syntax' */ 
void	echo_print(t_exec_data *d, char *str)
{
	int	syntax;
	int	flag_dq;
	int	flag_sq;
	int	i;

	syntax = verify_syntax(d, str);
	if (syntax == 1)
	{
		i = 0;
		flag_sq = 1;
		flag_dq = 1;
		while (str[i])
		{
			if (str[i] == '\"' && flag_sq == 1)
				flag_dq *= -1;
			else if (str[i] == '\'' && flag_dq == 1)
				flag_sq *= -1;
			else if (str[i] != '\"' || str[i] != '\'')
				ft_printf(1, "%c", str[i]);
			i++;
		}
	}
}

/* Verifies if the single and double quotes sintax is correct */
/* If is correct returns (1) otherwise prints out error message and */
/* returns (0) */
int	verify_syntax(t_exec_data *d, char *str)
{
	int	flag_dq;
	int	flag_sq;
	int	i;

	i = 0;
	flag_sq = 1;
	flag_dq = 1;
	while (str[i])
	{
		if (str[i] == '\"' && flag_sq == 1)
			flag_dq *= -1;
		else if (str[i] == '\'' && flag_dq == 1)
			flag_sq *= -1;
		i++;
	}
	if (flag_dq == 1 && flag_sq == 1)
		return (1);
	if (flag_dq == -1)
		d->int_error_code = ERROR_B_TOKEN_D;
	else if (flag_sq == -1)
		d->int_error_code = ERROR_B_TOKEN_S;
	d->term_status = 258;
	ft_error_handler(NULL, d);
	return (0);
}
