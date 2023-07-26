/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_check_built_in.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:37:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/26 21:52:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strtolower(char *str)
{
	if (!str || !*str)
		return ;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
		*str += ('a' - 'A');
		str++;
	}
}

int	ft_executor_check_built_in(t_exec_data	*d)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = ft_strdup(d->exec_args[0]);
	ft_strtolower(tmp);
	if (!ft_strncmp("echo", tmp, ft_strlen(tmp)))
		c++;
	else if (!ft_strncmp("cd", tmp, ft_strlen(tmp)))
		c++;
	else if (!ft_strncmp("pwd", tmp, ft_strlen(tmp)))
		c++;
	else if (!ft_strncmp("export", tmp, ft_strlen(tmp)))
		c++;
	else if (!ft_strncmp("unset", tmp, ft_strlen(tmp)))
		c++;
	else if (!ft_strncmp("env", tmp, ft_strlen(tmp)))
		c++;
	free (tmp);
	if (c)
		return (1);
	else
		return (0);
}
