/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/21 13:40:53 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_lines(char **str);

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

/* Inserts 'line' at the end of 'src' */
/* Function uses triple pointer, therefore the environment variable */
/* must be passed dereferenced with & */
/* If something goes wrong returns NULL otherwise returns 'dst' */
char	**add_var_to_env(char ***src, char *line)
{
	int		lines;
	int		i;
	char	**dst;

	if (!src || !*src || !line)
		return (NULL);
	lines = count_env_lines(*src);
	dst = (char **)malloc(sizeof(char *) * (lines + 2));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		dst[i] = ft_strdup((*src)[i]);
		free((*src)[i]);
		i++;
	}
	dst[i++] = ft_strdup(line);
	dst[i] = NULL;
	free (*src);
	*src = dst;
	return (dst);
}

/* Removes all lines starting with 'var' from 'src' */
/* Function uses triple pointer, therefore the environment variable */
/* must be passed dereferenced with & */
/* If something goes wrong returns NULL otherwise returns 'dst' */
char	**del_var_from_env(char ***src, char *var)
{
	int		lines;
	int		i;
	int		j;
	char	**dst;

	if (!src || !*src || !var)
		return (NULL);
	lines = count_env_lines(*src);
	dst = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (i < lines)
	{
		if (ft_strnstr((*src)[i], var, ft_strlen(var)) == NULL)
			dst[j++] = ft_strdup((*src)[i]);
		free((*src)[i]);
		i++;
	}
	dst[i] = NULL;
	free (*src);
	*src = dst;
	return (dst);
}

int	count_env_lines(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
