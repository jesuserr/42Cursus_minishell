/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:06:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 21:38:56 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_t_s_cmd_trim_redi1(char **cmd, char **tmp)
{
	char	typeq;

	if (**cmd == '\'' || **cmd == '\"')
	{
		typeq = **cmd;
		**tmp = **cmd;
		(*tmp)++;
		(*cmd)++;
		while (**cmd && **cmd != typeq)
		{
			**tmp = **cmd;
			(*tmp)++;
			(*cmd)++;
		}
	}
	else if ((ft_isdigit(**cmd) || **cmd == '&')
		&& (**(cmd + 1) == '<' || **(cmd + 1) == '>'))
		(*cmd)++;
}

void	p_t_s_cmd_trim_redi2(char **cmd, char **tmp)
{
	char	typeq;

	if (**cmd == '<' || **cmd == '>')
	{
		while (**cmd == '<' || **cmd == '>')
			(*cmd)++;
		while (**cmd == ' ')
			(*cmd)++;
		while (**cmd == '\'' || **cmd == '\"')
		{
			typeq = **cmd;
			(*cmd)++;
			while (**cmd && **cmd != typeq)
				(*cmd)++;
		}	
		while (**cmd && **cmd != ' ' && **cmd != '|'
			&& **cmd != ';' && **cmd != '&')
			(*cmd)++;
	}
	else
	{
		**tmp = **cmd;
		(*tmp)++;
		(*cmd)++;
	}
}

char	*p_t_s_cmd_trim_redi(char *cmd)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!tmp)
		ft_error("Unable to allocate memory in p_t_s_cmd_trim_redi");
	tmp1 = tmp;
	while (cmd && *cmd && *cmd != '|' && *cmd != ';' && *cmd != '&')
	{
		p_t_s_cmd_trim_redi1(&cmd, &tmp);
		p_t_s_cmd_trim_redi2(&cmd, &tmp);
	}
	tmp = ft_strtrim(tmp1, " ");
	free (tmp1);
	return (tmp);
}

void	p_t_s_cmd(char *block, char **cmd)
{
	*cmd = p_t_s_cmd_trim_redi(block);
}
