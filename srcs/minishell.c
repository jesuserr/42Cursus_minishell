/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:58:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/28 10:21:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_readcmdline(t_global *gd)
{
	char	*line;

	line = 0;
	while (ft_strncmp(line, "exit", ft_strlen(line)) != 0)
	{
		if (line)
			free(line);
		line = readline(PROMPT);
		if (line && *line && ft_strncmp(line, "exit", ft_strlen(line)) != 0)
		{
			add_history(line);
			ft_executor(parser(line, gd), gd);
		}
	}
	if (line)
		free(line);
}

void	ft_startmsg(void)
{
	printf(STARTMSG);
}

int	main(int argc, char **argv, char **env)
{
	t_global	gd;

	(void) argv;
	(void) argc;
	gd.env = ft_calloc(1, sizeof(char ***));
	*gd.env = copy_dbl_char_pointer(env);
	gd.last_status = 0;
	ft_startmsg();
	ft_readcmdline(&gd);
	free_split(*gd.env, 0);
	free(gd.env);
	return (0);
}
