/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_error2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:37:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/08 16:20:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	error_redi_pattern(char *line, char pattern)
{
	char	deli;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			deli = *line;
			line++;
			while (*line && *line != deli)
				line++;
			line++;
		}
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
		line++;
	}
	return (-1);
}
