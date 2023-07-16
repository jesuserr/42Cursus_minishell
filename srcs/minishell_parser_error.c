/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:24:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/16 23:10:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	error_redi_pattern(char *line, char pattern)
{
	while (*line)
	{
		if (*line == pattern)
		{
			while (*line == pattern)
				line++;
			while (*line == ' ')
				line++;
			if (*line == '|' || *line == ';' || *line == '&'
				|| *line == '>' || *line == '<' || !*line)
				return (*line);
		}
		else
			line++;
	}
	return (-1);
}

int	p_common_errors2(char *line)
{
	char	t_e;
	char	tmp[500];

	t_e = error_redi_pattern(line, '<');
	if (t_e > -1)
	{
		if (!t_e)
			sprintf(tmp, "syntax error near unexpected token EOF");
		else
			sprintf(tmp, "syntax error near unexpected token '%c'", t_e);
		ft_error_shell(tmp);
		return (1);
	}
	t_e = error_redi_pattern(line, '>');
	if (t_e > -1)
	{
		if (!t_e)
			sprintf(tmp, "syntax error near unexpected token EOF");
		else
			sprintf(tmp, "syntax error near unexpected token '%c'", t_e);
		ft_error_shell(tmp);
		return (1);
	}
	return (0);
}

int	p_common_errors1(char *line)
{
	if (ft_strnstr(line, ",", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token ','");
		return (1);
	}
	else if (ft_strnstr(line, "<<<<", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '<'");
		return (1);
	}
	return (0);
}

int	p_common_errors(char *line)
{
	if (ft_strnstr(line, "|||", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '||'");
		return (1);
	}
	else if (ft_strnstr(line, ";;", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token ';;'");
		return (1);
	}
	else if (ft_strnstr(line, "&&&", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '&'");
		return (1);
	}
	else if (p_t_s_type(line))
	{
		ft_error_shell("syntax error near unexpected token at EOL");
		return (1);
	}
	return (p_common_errors1(line) + p_common_errors2(line));
}
