/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:27:35 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/09 20:56:49 by cescanue         ###   ########.fr       */
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

void	ft_error_handler(int error, char *str)
{
	if (error == ERROR_XXX)
		perror("Undefined Error");
	else if (error == ERROR_CMD)
	{
		printf("minishell: command not found: %s\n", str);
		free(str);
		exit(127);
	}
	exit(EXIT_FAILURE);
}
