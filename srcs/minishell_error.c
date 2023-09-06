/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:46:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 23:20:25 by jesuserr         ###   ########.fr       */
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

void	ft_error_handler2(char *str, t_exec_data *d)
{
	(void) str;
	if (d->int_error_code == ERROR_FORK)
		ft_printf(2, "minishell: fork: Resource temporarily unavailable\n");
	else if (d->int_error_code == ERROR_MALLOC)
		ft_printf(2, "minishell: malloc: Cannot allocate memory\n");
	else if (d->int_error_code == ERROR_DUP)
		ft_printf(2, "minishell: dup: Cannot duplicate file descriptor\n");
	else if (d->int_error_code == ERROR_NOPERM_CD)
		ft_printf(2, "minishell: %s: Permission denied\n", str);
	else if (d->int_error_code == ERROR_TOOLONG)
		ft_printf(2, "minishell: %s: File name too long\n", str);
	return ;
}

/* Prints out error messages according to BASH through STDERR */
/* Custom text message can be additionally sent through *str */
void	ft_error_handler(char *str, t_exec_data *d)
{
	g_info->last_status = d->term_status;
	if (d->int_error_code == ERROR_CMDNOT)
		ft_printf(2, "minishell: %s: command not found\n", d->exec_args[0]);
	else if (d->int_error_code == ERROR_NOFILE)
		ft_printf(2, "minishell: %s: No such file or directory\n", str);
	else if (d->int_error_code == ERROR_NOPERM)
		ft_printf(2, "minishell: %s: Permission denied\n", d->exec_args[0]);
	else if (d->int_error_code == ERROR_NODIR)
		ft_printf(2, "minishell: %s: Not a directory\n", str);
	else if (d->int_error_code == ERROR_B_TOKEN_D)
		ft_printf(2, "minishell: syntax error near unexpected token `\"\'\n");
	else if (d->int_error_code == ERROR_B_TOKEN_S)
		ft_printf(2, "minishell: syntax error near unexpected token `\'\'\n");
	else if (d->int_error_code == ERROR_B_EXPORT)
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", str);
	else if (d->int_error_code == ERROR_B_NOHOME)
		ft_printf(2, "minishell: cd: HOME not set\n");
	else if (d->int_error_code == ERROR_B_UNSET)
		ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", str);
	else if (d->int_error_code == ERROR_B_PWD)
		ft_printf(2, "minishell: getcwd: failed: No such file or directory\n");
	else
		ft_error_handler2(str, d);
	return ;
}
