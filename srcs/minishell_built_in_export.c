/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_in_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:09:57 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/29 13:44:21 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*env_print_order(t_exec_data *d);
void	insert_var(t_exec_data *d);
void	export_var(t_exec_data *d);
void	insert_content_var(t_exec_data *d, char **split);

/* If no arguments are provided prints all the environment variables */
/* sorted alphabetically, adding "declare -x" at the beginning of each line */
/* If arguments are provided calls 'export_var' function */
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
	else
		export_var(d);
	return (0);
}

/* Before inserting the var it is checked if the var name meets requirements */
/* for allowed characters (name must be alphanumeric, '_' allowed anywhere */
/* and numbers not allowed at the beginning) */
void	export_var(t_exec_data *d)
{
	size_t	i;
	char	**split;
	int		flag;

	flag = 0;
	split = ft_split(d->exec_args[1], '=');
	i = 0;
	while (i++ < ft_strlen(split[0]))
	{
		if (!(ft_isalnum((split[0][i - 1])) || split[0][i -1] == '_') || \
		d->exec_args[1][0] == '=' || ft_isdigit(d->exec_args[1][0]))
		{
			d->int_error_code = ERROR_B_EXPORT;
			d->term_status = 1;
			ft_error_handler(d->exec_args[1], d);
			flag = 1;
			break ;
		}
	}
	free_split(split, NULL);
	if (flag == 0)
		insert_var(d);
}

/* Analyzes the content of the var (empty or with content) and acts in */
/* consequence. If the var name is XXX, XXX= or XXX="", it inserts XXX="" */
/* in the environment variable */
void	insert_var(t_exec_data *d)
{
	char	**split;
	char	*var_equal;
	char	*var_quotes;

	split = ft_split(d->exec_args[1], '=');
	if (!(split[1]) || (!ft_strncmp(split[1], "\"\"", 2) && \
	ft_strlen(split[1]) == 2))
	{
		var_equal = ft_strjoin(split[0], "=");
		var_quotes = ft_strjoin(var_equal, "\"\"");
		add_var_to_env(d->env, var_quotes);
		double_free(var_equal, var_quotes);
	}
	else
		insert_content_var(d, split);
	free_split(split, NULL);
}

/* Used to insert var when then var_name is VAR="XXX" or VAR=XXX */
void	insert_content_var(t_exec_data *d, char **split)
{
	char	*var_equal;
	char	*var_quotes;
	char	*var_value;
	char	*temp_1;
	char	*temp_2;

	var_value = ft_strtrim(split[1], "\"\'");
	if (ft_strchr(var_value, '\"'))
		d->term_status = 1;
	else
	{
		var_equal = ft_strjoin(split[0], "=");
		temp_1 = ft_strjoin(var_equal, "\"");
		temp_2 = ft_strjoin(temp_1, var_value);
		var_quotes = ft_strjoin(temp_2, "\"");
		add_var_to_env(d->env, var_quotes);
		double_free(var_quotes, var_equal);
		double_free(temp_1, temp_2);
	}
	free(var_value);
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
