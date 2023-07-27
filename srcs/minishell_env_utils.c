/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:44:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/27 16:38:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_existance(char **env, char *var);
char	**del_existing_var(char ***src, char *line);

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
	while ((*d->env)[i])
	{
		if (ft_strnstr((*d->env)[i], name_equal, ft_strlen(name_equal)) != NULL)
		{
			result = ft_strdup((*d->env)[i] + ft_strlen(name_equal));
			free(name_equal);
			return (result);
		}
		i++;
	}
	free(name_equal);
	return (NULL);
}

/* Inserts 'line' at the end of 'src' - 'line' consists of var name + value */
/* Function uses triple pointer, therefore the environment variable */
/* must be passed dereferenced with & */
/* If 'src' or 'line' are NULL or any malloc fails, NULL is returned */
/* If variable contained in 'line' is already inside 'src', it is replaced */
/* Returns pointer to new created 'dst' on success */
char	**add_var_to_env(char ***src, char *line)
{
	int		lines;
	int		i;
	char	**dst;

	if (!src || !*src || !line)
		return (NULL);
	lines = count_dbl_char_lines(*src);
	if (check_existance(*src, line) == 1)
		if (!del_existing_var(src, line))
			return (NULL);
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


/* Removes line starting with 'var' from 'src' - 'var' expected without '=' */
/* Function uses triple pointer, therefore the environment variable */
/* must be passed dereferenced with & */
/* If 'src' or 'var' are NULL or 'var' is not contained inside 'src' */
/* NULL is returned, otherwise it returns the created 'dst' */
char	**del_var_from_env(char ***src, char *var)
{
	int		lines;
	int		cont[2];	
	char	**dst;
	char	*var_equ;

	if ((check_existance(*src, var) == 0) || !src || !*src || !var)
		return (NULL);
	lines = count_dbl_char_lines(*src);
	dst = (char **)malloc(sizeof(char *) * (lines));
	if (!dst)
		return (NULL);
	var_equ = ft_strjoin(var, "=");
	cont[0] = 0;
	cont[1] = 0;
	while (cont[0] < lines)
	{
		if (ft_strnstr((*src)[cont[0]], var_equ, ft_strlen(var_equ)) == NULL)
			dst[cont[1]++] = ft_strdup((*src)[cont[0]]);
		free((*src)[cont[0]++]);
	}
	dst[cont[1]] = NULL;
	free (*src);
	free (var_equ);
	*src = dst;
	return (dst);
}

/* Verifies if the variable 'var' already exists inside 'env' */
/* If already exists returns (1) to inform the adding/removal functions */
/* If 'var' is not contained on 'env' returns (0) */
int	check_existance(char **env, char *var)
{
	int		i;
	char	*var_equal;
	char	**split_var;

	split_var = ft_split(var, '=');
	var_equal = ft_strjoin(split_var[0], "=");
	free_split(split_var, NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], var_equal, ft_strlen(var_equal)) != NULL)
		{
			free(var_equal);
			return (1);
		}
		i++;
	}
	free(var_equal);
	return (0);
}

/* Used by function 'add_var_to_env' to remove an existing variable before */
/* replacing it */
char	**del_existing_var(char ***src, char *line)
{
	char	**split_name;

	split_name = ft_split(line, '=');
	if (!del_var_from_env(src, split_name[0]))
	{
		free_split(split_name, NULL);
		return (NULL);
	}
	free_split(split_name, NULL);
	return (*src);
}
