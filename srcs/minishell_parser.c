/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 19:24:40 by cescanue         ###   ########.fr       */
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
