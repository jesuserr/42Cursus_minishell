/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/20 12:28:37 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(t_exec_data *d, char *name)
{
	char	*result;
	int		i;

	i = 0;
	while (ft_strnstr(d->env[i], name, ft_strlen(name)) == NULL)
		i++;
	result = ft_strdup(d->env[i] + ft_strlen(name));
	return (result);
}

//ft_printf(1, "\n%s\n", getenv(variable));
//result  = getenv(name);
//return (result);
