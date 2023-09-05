/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:04:11 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/05 13:33:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Swaps the values of two variables */
void	swap_values(int *a, int *b)
{
	int	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

/* Returns a formatted prompt that contains the current working folder */
/* Returned str must be freed by the calling function */
/* To be used inside ft_readcmdline - How to use it: */
/* char	*pwd; */
/* pwd = pwd_as_prompt(); */
/* line = readline(pwd); */
/* free (pwd); */
char	*pwd_as_prompt(void)
{
	char	buf[PATH_MAX];
	char	*temp;
	char	*pwd;
	char	**split;
	int		i;

	pwd = getcwd(buf, PATH_MAX);
	if (!pwd)
	{
		pwd = ft_strdup("/");
		split = ft_split(pwd, '/');
		free (pwd);
	}
	else
		split = ft_split(pwd, '/');
	i = 0;
	while (split[i])
		i++;
	if (i > 0)
		temp = ft_strjoin("💾 \033[0;94m/", split[i - 1]);
	else
		temp = ft_strdup("💾 \033[0;94m/");
	pwd = ft_strjoin(temp, " \033[0;37m");
	free_split(split, temp);
	return (pwd);
}
