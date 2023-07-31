/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_echo.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:12:42 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/31 21:41:20 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_printf(STDOUT_FILENO, "%s", d->exec_args[i++]);
		if (d->exec_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (!flag && d->term_status == 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}

/* Verifies if the single and double quotes syntax is correct */
/* If is correct returns (1) otherwise prints out error message and */
/* returns (0) */
int	verify_syntax_quotes(char *str)
{
	int			flag_dq;
	int			flag_sq;
	int			i;
	t_exec_data	d;

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
		d.int_error_code = ERROR_B_TOKEN_D;
	else if (flag_sq == -1)
		d.int_error_code = ERROR_B_TOKEN_S;
	d.term_status = 258;
	ft_error_handler(NULL, &d);
	return (0);
}

/* Creates a 'new_str' with the quoting syntax interpreted */
/* Created 'new_str' must be freed by the calling function */
char	*quotes_analysis(char *str)
{
	int		flag_dq;
	int		flag_sq;
	int		i;
	int		j;
	char	*new_str;

	new_str = (char *)ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	j = 0;
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
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
