/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struck_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:01:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 17:02:33 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_count(char *block)
{
	int	count;

	count = 0;
	while (*block != ' ' && *block != '|' && *block != ';' && *block
		!= '&' && *block != '>' && *block != '<' && *block)
	{
		count++;
		block++;
	}
	return (count);
}
