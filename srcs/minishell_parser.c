/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/08 22:17:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char *line)
{
	char	*tline;

	tline = p_identify_blocks(line);
	p_common_errors(tline);
	ft_printf("%s\n", tline);
}

void	p_common_errors(char *line)
{
	if (ft_strnstr(line, "|||", ft_strlen(line)))
		ft_error("syntax error near unexpected token '||'");
	if (ft_strnstr(line, ";;", ft_strlen(line)))
		ft_error("syntax error near unexpected token ';;'");
	if (ft_strnstr(line, "&&&", ft_strlen(line)))
		ft_error("syntax error near unexpected token '&'");
}
