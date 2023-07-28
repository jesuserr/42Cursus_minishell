/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_history.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:24:46 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/28 15:52:31 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_history(t_exec_data *d)
{
	HIST_ENTRY	**his;
	int			count;

	(void) d;
	count = 1;
	his = history_list();
	while (*his)
	{
		ft_printf(1, " %4d  %s\n", count, (*his)->line);
		his++;
		count++;
	}
	return (0);
}
