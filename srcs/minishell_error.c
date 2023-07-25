/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:46:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/25 21:31:58 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *error)
{
	ft_printf(STDERR_FILENO, "%s\n", error);
	exit(0);
}

void	ft_error_shell(char *error)
{
	char	errortmp[500];

	ft_strlcpy(errortmp, "Minishell: ", 500);
	ft_strlcat(errortmp, error, 500);
	ft_printf(STDERR_FILENO, "%s\n", errortmp);
}

/* Prints out error messages according to BASH through STDERR */
/* Custom text message can be additionally sent through *str */
void	ft_error_handler(char *str, t_exec_data *d)
{
	if (d->int_error_code == ERROR_XXX)
	{
		perror("Undefined Error");
		exit(EXIT_FAILURE);
	}
	else if (d->int_error_code == ERROR_CMDNOT)
		ft_printf(STDERR_FILENO, "minishell: %s: command not found\n", d->exec_args[0]);
	else if (d->int_error_code == ERROR_NOFILE)
		ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
	else if (d->int_error_code == ERROR_NOPERM)
		ft_printf(STDERR_FILENO, "minishell: %s: Permission denied\n", d->exec_args[0]);
	else if (d->int_error_code == ERROR_NODIR)
		ft_printf(STDERR_FILENO, "minishell: %s: Not a directory\n", str);
	else if (d->int_error_code == ERROR_B_NOHOME)
		ft_printf(STDERR_FILENO, "minishell: cd: HOME not set\n");
	else if (d->int_error_code == ERROR_B_UNSET)
		ft_printf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", str);
	else if (d->int_error_code == ERROR_B_PWD)
		ft_printf(STDERR_FILENO, "minishell: getcwd: failed: No such file or directory\n");
	else if (d->int_error_code == ERROR_FORK)
		ft_printf(STDERR_FILENO, "minishell: fork: retry: Resource temporarily unavailable\n");
	else if (d->int_error_code == ERROR_MALLOC)
		ft_printf(STDERR_FILENO, "minishell: malloc: Cannot allocate memory\n");
	else if (d->int_error_code == ERROR_DUP)
		ft_printf(STDERR_FILENO, "minishell: dup: Cannot duplicate file descriptor\n");
	return ;
}
