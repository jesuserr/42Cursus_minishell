/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built_ins_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:09:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/29 14:09:38 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Returns path working directory using getcwd instead of our environment */
/* PWD variable to avoid failure in case that PWD is not present */
/* Returned value must be freed by the calling function */
char	*obtain_pwd(t_exec_data *d)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		d->int_error_code = ERROR_B_PWD;
		ft_error_handler(NULL, d);
		return (NULL);
	}
	return (ft_strdup(pwd));
}

/* Swaps the values of two variables */
void	swap_values(int *a, int *b)
{
	int	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

/* Used by built_in_export in order to initialize an array with the same */
/* number of elements than the enviroment variable with numbers in */
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

void	export_var_error(t_exec_data *d, int j, int *flag)
{
	d->int_error_code = ERROR_B_EXPORT;
	d->term_status = 1;
	ft_error_handler(d->exec_args[j], d);
	*flag = 1;
}