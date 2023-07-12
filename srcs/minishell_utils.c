/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:04:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/12 21:09:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Allows to free at the same time a double pointer (typically from ft_split) */
/* and optionally a single pointer, if provided */
void	free_split(char **str_1, char *str_2)
{
	size_t	i;

	if (str_2)
		free(str_2);
	i = 0;
	while (str_1 && str_1[i])
		free(str_1[i++]);
	free(str_1);
}
