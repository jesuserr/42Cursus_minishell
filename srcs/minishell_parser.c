/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/07 21:45:32 by cescanue         ###   ########.fr       */
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

void	p_identify_blocks1(char *tmp, char *tmp1)
{
	while (*tmp)
	{
		if (*tmp == ';' || *tmp == '|' || *tmp == '&')
		{
			*tmp1 = ',';
			tmp1++;
			*tmp1 = *tmp;
			while (*(tmp + 1) == ' ' || *(tmp + 1) == ';'
				|| *(tmp + 1) == '|' || *(tmp + 1) == '&')
			{
				if (*(tmp + 1) == ' ')
					while (*(tmp + 1) == ' ')
						tmp++;
				else
				{
					tmp++;
					tmp1++;
					*tmp1 = *tmp;
				}
			}
			tmp1++;
			*tmp1 = ',';
		}
		else
			*tmp1 = *tmp;
		tmp++;
		tmp1++;
	}
}

char	*p_identify_blocks(char *line)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		blocks;

	tmp = line;
	blocks = 0;
	while (*tmp)
	{
		if (*tmp == ';' || *tmp == '|' || *tmp == '&')
			blocks++;
		tmp++;
	}
	tmp1 = ft_calloc(ft_strlen(line) + blocks * 2, sizeof(char));
	tmp2 = tmp1;
	tmp = line;
	p_identify_blocks1(tmp, tmp1);
	return (tmp2);
}
