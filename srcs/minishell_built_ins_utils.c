/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:09:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/08 14:42:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Returns path of the current working directory using getcwd instead of our */
/* environment PWD variable to avoid failure in case that PWD is not present */
/* If getcwd result is NULL, the path is set in the root in order to avoid */
/* issues, i.e.: the user has deleted the current working directory */
/* Returned value must be freed by the calling function */
char	*obtain_pwd(void)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
		return (ft_strdup("/"));
	return (ft_strdup(pwd));
}

/* Used by built_in_export in order to initialize an array with the same */
/* number of elements than the environment variable with numbers in */
/* correlative order - created mainly to meet norminette */
void	init_array(int **array, int env_l)
{
	int	i;

	i = 0;
	while (i < env_l)
	{
		(*array)[i] = i;
		i++;
	}
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

/* Prints out error message when the environment variable to be */
/* added with 'export' does not meet the variable name requirements */
void	export_var_error(t_exec_data *d, int j, int *flag)
{
	d->int_error_code = ERROR_B_EXPORT;
	d->term_status = 1;
	ft_error_handler(d->exec_args[j], d);
	*flag = 1;
}

/* Prints out error message if export arguments are '=' or "" or '' */
void	export_equal_error(t_exec_data *d)
{
	d->int_error_code = ERROR_B_EXPORT;
	d->term_status = 1;
	ft_error_handler(d->exec_args[1], d);
}
