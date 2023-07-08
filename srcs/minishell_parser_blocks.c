/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_blocks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 22:16:10 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/08 22:16:42 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_identify_blocks2(char **tmp, char **tmp1)
{
	if (*(*tmp + 1) == ' ')
		while (*(*tmp + 1) == ' ')
			(*tmp)++;
	else
	{
		(*tmp)++;
		(*tmp1)++;
		**tmp1 = **tmp;
	}
}

void	p_identify_blocks3(char **tmp, char **tmp1)
{
	char	*tco;

	if (**tmp == '"' || **tmp == '\'')
	{
		**tmp1 = **tmp;
		(*tmp1)++;
		tco = *tmp;
		(*tmp)++;
		while (**tmp && **tmp != *tco)
		{
			**tmp1 = **tmp;
			(*tmp1)++;
			(*tmp)++;
		}
	}
}

void	p_identify_blocks1(char *tmp, char *tmp1)
{
	while (*tmp)
	{
		p_identify_blocks3(&tmp, &tmp1);
		if (*tmp == ';' || *tmp == '|' || *tmp == '&')
		{
			*tmp1 = ',';
			tmp1++;
			*tmp1 = *tmp;
			while (*(tmp + 1) == ' ' || *(tmp + 1) == ';'
				|| *(tmp + 1) == '|' || *(tmp + 1) == '&')
			{
				p_identify_blocks2(&tmp, &tmp1);
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
