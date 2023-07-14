/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct_cmd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:06:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/14 08:06:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_t_s_cmd_count2(char *block, int *count)
{
	char	deli;

	while (*(block) && *block != '|' && *block != ';'
		&& *block != '&' && *block != '<' && *block != '>')
	{
		deli = *block;
		if (*block == '"' || *block == '\'')
		{
			while (*(block++) && *block != deli)
				(*count)++;
			(*count)++;
		}
		else
		{
			block++;
			(*count)++;
		}
	}
}

int	p_t_s_cmd_count(char *block, char **blockcmd)
{
	int	count;

	count = 0;
	while (*block == ' ' || *block == '<' || *block == '>')
	{
		while (*block == ' ')
			block++;
		if (*block == '<' || *block == '>')
		{
			while (*block == '<')
				block++;
			while (*block == '>')
				block++;
			while (*block == ' ')
				block++;
			while (*block && *block != ' ')
				block++;
		}
	}
	*blockcmd = block;
	p_t_s_cmd_count2(block, &count);
	return (count);
}

void	p_t_s_cmd(char *block, char **cmd)
{
	char	*blockcmd;
	int		len;

	len = p_t_s_cmd_count(block, &blockcmd) + 1;
	*cmd = ft_calloc(len, sizeof(char));
	if (!*cmd)
		ft_error("Unable to allocate memory in p_t_s_cmd");
	ft_strlcpy(*cmd, blockcmd, len);
}
