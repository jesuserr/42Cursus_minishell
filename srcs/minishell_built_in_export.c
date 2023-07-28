/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:09:57 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/28 12:12:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_export(t_exec_data *d)
{
	int	i;
	int	flag;

	if (!d->exec_args[1])
	{
		ft_printf(STDOUT_FILENO, "\n");
		return (0);
	}
	i = 1;
	flag = 0;
	if (!(ft_strncmp(d->exec_args[1], "-n", 2)) && \
	ft_strlen(d->exec_args[1]) == 2)
	{
		flag = 1;
		i++;
	}
	while (d->exec_args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", d->exec_args[i++]);
		if (d->exec_args[i])
			ft_printf(STDOUT_FILENO, " ");
	}
	if (!flag)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
