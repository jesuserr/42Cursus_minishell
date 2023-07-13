/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 13:20:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char *line)
{
	char	*tline;
	char	**cmds;
	char	**tcmds;

	cmds = 0;
	tcmds = 0;
	tline = 0;
	if (!p_common_errors(line))
	{
		tline = p_identify_blocks(line);
		tline = p_replace_env(tline);
		cmds = ft_split(tline, ',');
		tcmds = cmds;
	}
	while (tcmds && *tcmds)
	{
		p_t_s(*tcmds);
		tcmds++;
	}
	free_split(cmds, tline);
}

char	error_redi_in(char *line)
{
	while (*line)
	{
		if (*line == '<')
		{
			while (*line == '<')
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

int	p_common_errors(char *line)
{
	char	token_error;
	char	tmp[500];

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
	else if (ft_strnstr(line, ",", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token ','");
		return (1);
	}
	else if (ft_strnstr(line, "<<<<", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token '<'");
		return (1);
	}
	token_error = error_redi_in(line);
	if (token_error > -1)
	{
		if (!token_error)
			sprintf(tmp, "syntax error near unexpected token EOF");
		else
			sprintf(tmp, "syntax error near unexpected token '%c'",
				token_error);
		ft_error_shell(tmp);
		return (1);
	}
	return (0);
}
