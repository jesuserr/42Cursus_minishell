/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:27:35 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/12 19:17:52 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *error)
{
	ft_printf("%s\n", error);
	exit(0);
}

void	ft_error_shell(char *error)
{
	char	errortmp[500];

	ft_strlcpy(errortmp, "Minishell: ", 500);
	ft_strlcat(errortmp, error, 500);
	ft_printf("%s\n", errortmp);
}

void	ft_error_handler(char *str, t_exec_data *d)
{
	if (d->int_error_code == ERROR_XXX)
	{
		perror("Undefined Error");
		exit(EXIT_FAILURE);
	}
	else if (d->int_error_code == ERROR_CMDNOT)
		ft_printf("minishell: %s: command not found\n", str);
	else if (d->int_error_code == ERROR_NOFILE)
		ft_printf("minishell: %s: No such file or directory\n", str);
	else if (d->int_error_code == ERROR_NOPERM)
		ft_printf("minishell: %s: Permission denied\n", str);
	else if (d->int_error_code == ERROR_FORK)
		ft_printf("minishell: fork: retry: Resource temporarily unavailable\n");
	return ;
}
