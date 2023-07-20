/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/20 20:02:15 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Simulates function getenv() but using minishell environment variable */
/* Function getenv() disregards everything after first '=', this behaviour */
/* has been replicated, function also accepts the variable with or without */
/* character '=' same as getenv() */
/* If variable is not found NULL is returned */
char	*get_env_var(t_exec_data *d, char *name)
{
	int		i;
	char	*name_equal;
	char	**split_name;
	char	*result;

	if (!name || name[0] == '=')
		return (NULL);
	split_name = ft_split(name, '=');
	name_equal = ft_strjoin(split_name[0], "=");
	free_split(split_name, NULL);
	i = 0;
	while (d->env[i])
	{
		if (ft_strnstr(d->env[i], name_equal, ft_strlen(name_equal)) != NULL)
		{
			result = ft_strdup(d->env[i] + ft_strlen(name_equal));
			free(name_equal);
			return (result);
		}
		i++;
	}
	return (NULL);
}
