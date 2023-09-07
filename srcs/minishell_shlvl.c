/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:11:19 by jesuserr          #+#    #+#             */
/*   Updated: 2023/09/07 20:05:15 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_warning_shlvl(int shell_level);
char	*get_env_var_shlvl(t_global *gd, char *name);

/* Updates $SHLVL environment variable every time that minishell is invoked */
void	update_shell_level(t_global *gd)
{
	char	*shell_level_str;
	int		shell_level;
	char	*shlvl;
	char	*var;

	shell_level_str = get_env_var_shlvl(gd, "SHLVL");
	if (!shell_level_str)
		shell_level = 0;
	else
		shell_level = ft_atoi(shell_level_str);
	if (shell_level < 0)
		shell_level = 0;
	else if (shell_level >= 1000)
	{
		print_warning_shlvl(shell_level);
		shell_level = 1;
	}
	else
		shell_level++;
	shlvl = ft_itoa(shell_level);
	var = ft_strjoin("SHLVL=", shlvl);
	add_var_to_env(gd->env, var);
	free(shell_level_str);
	double_free (var, shlvl);
}

/* Absurd formatting just to meet Norminette (line exceeding 80 characters) */
void	print_warning_shlvl(int shell_level)
{
	ft_printf(2, \
	"minishell: warning: shell level (%d) too high, resetting to 1\n"\
	, shell_level + 1);
}

/* Simulates function getenv() but using minishell environment variable */
/* Function getenv() disregards everything after first '=', this behaviour */
/* has been replicated, function also accepts the variable with or without */
/* character '=' same as getenv() */
/* If variable is not found NULL is returned */
char	*get_env_var_shlvl(t_global *gd, char *name)
{
	int		i;
	char	*name_eq;
	char	**split_name;
	char	*result;

	if (!name || name[0] == '=')
		return (NULL);
	split_name = ft_split(name, '=');
	name_eq = ft_strjoin(split_name[0], "=");
	free_split(split_name, NULL);
	i = 0;
	while ((*gd->env)[i])
	{
		if (ft_strnstr((*gd->env)[i], name_eq, ft_strlen(name_eq)) != NULL)
		{
			result = ft_strdup((*gd->env)[i] + ft_strlen(name_eq));
			free(name_eq);
			return (result);
		}
		i++;
	}
	free(name_eq);
	return (NULL);
}
