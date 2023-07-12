/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/12 21:26:10 by cescanue         ###   ########.fr       */
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
	tline = p_identify_blocks(line);
	if (!p_common_errors(tline))
	{
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
	else if (ft_strnstr(line, ",", ft_strlen(line)))
	{
		ft_error_shell("syntax error near unexpected token ','");
		return (1);
	}
	return (0);
}
