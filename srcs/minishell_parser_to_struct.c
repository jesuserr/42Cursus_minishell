/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_to_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:55:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/13 16:11:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_t_s(char *block)
{
	t_token	*token;
	
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("Unable to allocate memory in p_t_s");
	p_t_s_pattern(block, "<", token);
	//from here is temporal
	//printf("->%s\n", block);
	free (token);
}
