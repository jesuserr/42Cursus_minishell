/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:27:35 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/08 20:08:52 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *error)
{
	perror(error);
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
