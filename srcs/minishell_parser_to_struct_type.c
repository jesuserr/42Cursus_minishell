/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct_type.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:03:06 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/14 08:10:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	p_t_s_type(char *block)
{
	int		type;
	char	*tblock;

	tblock = block;
	type = 0;
	while (*block)
		block++;
	block--;
	while (tblock != block && (*block == '|'
			|| *block == ';' || *block == '&' || *block == ' '))
		block--;
	if (ft_strnstr(block, "||", ft_strlen(block)))
		type = T_OR;
	else if (ft_strnstr(block, "&&", ft_strlen(block)))
		type = T_AND;
	else if (ft_strnstr(block, ";", ft_strlen(block)))
		type = T_SEMICOLON;
	else if (ft_strnstr(block, "|", ft_strlen(block)))
		type = T_PIPE;
	return (type);
}
