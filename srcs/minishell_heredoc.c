/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:50:30 by cescanue          #+#    #+#             */
/*   Updated: 2023/08/01 15:23:07 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc(char *sep)
{
	int		p[2];
	char	*str;

	str = 0;
	pipe(p);
	ft_printf(1, "> ");
	//str = get_next_line(0);
	while (str && (!ft_strnstr(str, sep, ft_strlen(str))
			|| (ft_strlen(str) - 1) != ft_strlen(sep)))
	{
		write(p[1], str, ft_strlen(str));
		if (str)
			free(str);
		ft_printf(1, "> ");
		str = get_next_line(0);
	}
	if (str)
		free(str);
	close (p[1]);
	return (p[0]);
}
