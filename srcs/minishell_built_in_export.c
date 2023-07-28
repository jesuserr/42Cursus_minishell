/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:09:57 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/28 18:32:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*env_print_order(t_exec_data *d);
int		longest_var(t_exec_data *d);

/* If no arguments are provided prints all the environment variables */
/* sorted alphabetically, adding "declare -x" at the beginning of each line */
/* No STDIN for this kind of built-in */
int	built_in_export(t_exec_data *d)
{
	int		*order;
	int		i;
	char	*msg;

	if (!d->exec_args[1])
	{
		order = env_print_order(d);
		if (!order)
			return (-1);
		i = 0;
		while ((*d->env)[i])
		{
			msg = ft_strjoin("declare -x ", (*d->env)[order[i++]]);
			ft_printf(STDOUT_FILENO, "%s\n", msg);
			free(msg);
		}
		free(order);
	}
	return (0);
}

/* Uses very basic sorting algorithm to determine the printing order of the */
/* environment variables - Returns an array indicating in which order the */
/* environment lines must be printed, if array creation fails returns NULL */
int	*env_print_order(t_exec_data *d)
{
	int	i;
	int	var_l;
	int	env_l;
	int	*p;

	var_l = longest_var(d);
	env_l = count_dbl_char_lines(*d->env);
	p = (int *)ft_calloc(env_l, sizeof(int));
	if (!p)
		return (NULL);
	init_array(&p, env_l);
	i = 0;
	while (env_l)
	{
		i = 0;
		while ((*d->env)[i + 1])
		{
			if (ft_strncmp((*d->env)[p[i]], (*d->env)[p[i + 1]], var_l) > 0)
				swap_values(&(p[i]), &(p[i + 1]));
			i++;
		}
		env_l--;
	}
	return (p);
}

/* Returns the length of the longest environment variable */
int	longest_var(t_exec_data *d)
{
	int	i;
	int	length;
	int	max_length;

	i = 0;
	max_length = 0;
	while ((*d->env)[i])
	{
		length = ft_strlen((*d->env)[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}
