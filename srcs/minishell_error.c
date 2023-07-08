/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:27:35 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/08 21:46:26 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *error)
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
