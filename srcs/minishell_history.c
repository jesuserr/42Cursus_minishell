/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:52:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/04 16:41:58 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_history(char *line)
{
	int		hpos;
	int		c;

	while (p2_strnstr(line, "!", ft_strlen(line)))
	{
		c = 2;
		line = p2_strnstr(line, "!", ft_strlen(line)) + 1;
		hpos = ft_atoi(line);
		if ((hpos < 0 && (history_length + hpos) < 0)
			|| hpos == 0 || hpos > history_length)
		{
			ft_printf(2, "Minishell: !%d: event not found\n", hpos);
			return (0);
		}
	}
	if (c == 2)
		return (2);
	return (1);
}

int	ft_line_new_size(char *line)
{
	int			size;
	int			count;
	int			hpos;
	HIST_ENTRY	**his;

	size = ft_strlen(line);
	while (p2_strnstr(line, "!", ft_strlen(line)))
	{
		line = p2_strnstr(line, "!", ft_strlen(line)) + 1;
		hpos = ft_atoi(line);
		if (hpos < 0)
			hpos = history_length + hpos + 1;
		his = history_list();
		count = 1;
		while (count < hpos)
		{
			his++;
			count++;
		}
		size += ft_strlen((*his)->line);
	}
	return (size);
}

void	ft_history_copy_his(char *line, char *tline, int size)
{
	HIST_ENTRY	**his;
	int			count;
	int			hpos;

	hpos = ft_atoi(line);
	count = 1;
	his = history_list();
	if (hpos < 0)
		hpos = history_length + hpos + 1;
	while (count < hpos)
	{
		his++;
		count++;
	}
	ft_strlcat(tline, (*his)->line, size);
}

char	*ft_history(char *line)
{
	char		*tline;
	char		*aline;
	char		*copyline;
	int			size;

	copyline = line;
	size = ft_line_new_size(line) + 1;
	tline = ft_calloc(size, sizeof(char));
	if (!tline)
		ft_error_shell("malloc: Cannot allocate memory in histoy");
	while (p2_strnstr(line, "!", ft_strlen(line)))
	{
		aline = line;
		line = p2_strnstr(line, "!", ft_strlen(line));
		ft_strlcat(tline, aline, (line++ - aline) + ft_strlen(tline) + 1);
		ft_history_copy_his(line, tline, size);
		if (*line == '-')
			line++;
		while (*line >= '0' && *line <= '9')
			line++;
	}
	ft_strlcat(tline, line, size);
	free (copyline);
	ft_printf(1, "%s\n", tline);
	return (tline);
}
