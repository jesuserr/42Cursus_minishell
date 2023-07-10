/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:27:35 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/10 12:55:53 by jesuserr         ###   ########.fr       */
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

/* Sería interesante hacernos un ft_printf_fd que imprima en fd 2 */
void	ft_error_handler(char *str, t_basic_data *d)
{
	if (d->int_error_code == ERROR_XXX)
	{
		perror("Undefined Error");
		exit(EXIT_FAILURE);
	}
	else if (d->int_error_code == ERROR_CMD)
		printf("minishell: %s: command not found\n", str);
	else if (d->int_error_code == ERROR_NOFILE)
		printf("minishell: %s: No such file or directory\n", str);
	return ;
}
