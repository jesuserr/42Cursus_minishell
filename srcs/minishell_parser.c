/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/07 14:49:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char *line)
{
	p_identify_blocks(line);
}

void	p_identify_blocks(char *line)
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
	while (*tmp)
	{
		if (*tmp == ';' || *tmp == '|' || *tmp == '&')
		{
			*tmp1 = ',';
			tmp1++;
			*tmp1 = *tmp;
			if (*(tmp + 1) == ';' || *(tmp + 1) == '|' || *(tmp + 1) == '&')
			{
				tmp++;
				tmp1++;
				*tmp1 = *tmp;
			}
			tmp1++;
			*tmp1 = ',';
		}
		else
			*tmp1 = *tmp;
		tmp++;
		tmp1++;
	}
	printf("blocks:%s", tmp2);
}