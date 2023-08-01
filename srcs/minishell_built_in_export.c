/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:09:57 by jesuserr          #+#    #+#             */
/*   Updated: 2023/08/01 13:19:30 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*env_print_order(t_exec_data *d);
void	format_export_output(t_exec_data *d, int *order, int i);
void	export_var(t_exec_data *d);
void	insert_var(t_exec_data *d, size_t index);

/* If no arguments are provided prints all the environment variables */
/* sorted alphabetically, adding "declare -x" at the beginning of each line */
/* If arguments are provided calls 'export_var' function */
/* The real export built-in can add multiple variables in one commnad line */
/* i.e. "export V1="A" V2="B" V3="C"", behaviour implemented */
/* No STDIN for this kind of built-in */
int	built_in_export(t_exec_data *d)
{
	int		*order;
	int		i;	

	if (!d->exec_args[1])
	{
		order = env_print_order(d);
		if (!order)
			return (-1);
		i = 0;
		while ((*d->env)[i])
		{
			format_export_output(d, order, i);
			i++;
		}
		free(order);
	}
	else
		export_var(d);
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

/* Prints out the environment variables as in bash, that means, adding */
/* 'declare -x' at the beginning and putting the value of the variable */
/* between double quotes */
void	format_export_output(t_exec_data *d, int *order, int i)
{
	char	**split;
	char	*msg;
	int		line_l;
	int		name_l;

	split = ft_split((*d->env)[order[i]], '=');
	line_l = ft_strlen((*d->env)[order[i]]);
	name_l = ft_strlen(split[0]);
	msg = ft_substr((*d->env)[order[i]], name_l + 1, line_l - name_l - 1);
	ft_printf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", split[0], msg);
	free_split(split, msg);
}

/* Before inserting the var it is checked if the var name meets requirements */
/* for allowed characters (name must be alphanumeric, '_' allowed anywhere */
/* and numbers not allowed at the beginning) */
void	export_var(t_exec_data *d)
{
	size_t	i;
	size_t	j;
	char	**split;
	int		flag;

	j = 1;
	while (d->exec_args[j])
	{
		flag = 0;
		split = ft_split(d->exec_args[j], '=');
		i = 0;
		while (i++ < ft_strlen(split[0]))
		{
			if (!(ft_isalnum((split[0][i - 1])) || split[0][i -1] == '_') || \
			d->exec_args[j][0] == '=' || ft_isdigit(d->exec_args[j][0]))
			{
				export_var_error(d, j, &flag);
				break ;
			}
		}
		free_split(split, NULL);
		if (flag == 0)
			insert_var(d, j);
		j++;
	}
}

/* Analyzes the content of the var (empty or with content) and acts in */
/* consequence. */
void	insert_var(t_exec_data *d, size_t j)
{
	char	**split;
	char	*var_equal;
	char	*var_total;

	split = ft_split(d->exec_args[j], '=');
	var_equal = ft_strjoin(split[0], "=");
	if (!(split[1]) || (!ft_strncmp(split[1], "\"\"", 2) && \
	ft_strlen(split[1]) == 2))
	{
		add_var_to_env(d->env, var_equal);
		free(var_equal);
	}
	else
	{
		var_total = ft_strjoin(var_equal, split[1]);
		add_var_to_env(d->env, var_total);
		double_free(var_total, var_equal);
	}
	free_split(split, NULL);
}
