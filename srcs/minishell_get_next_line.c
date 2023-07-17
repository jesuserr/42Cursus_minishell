/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_get_next_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:40:09 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 12:12:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	readffd(int fd, char **pbuffer)
{
	char	*temp;
	char	*new;

	temp = (char *) ft_calloc (sizeof (char), BUFFER_SIZE + 1);
	if (!temp)
		return (0);
	if (read(fd, temp, BUFFER_SIZE) <= 0)
	{
		free (temp);
		return (0);
	}
	else
	{
		if (!pbuffer[fd])
			pbuffer[fd] = temp;
		else
		{
			new = ft_strjoin(pbuffer[fd], temp);
			free(pbuffer[fd]);
			free(temp);
			pbuffer[fd] = new;
		}
	}
	return (1);
}

char	*ft_split_next_line(int fd, char **pbuffers)
{
	char	*temp;
	char	*rest;

	rest = ft_substr((ft_strchr(pbuffers[fd], '\n')), 1,
			ft_strlen(pbuffers[fd]));
	temp = ft_substr(pbuffers[fd], 0,
			ft_strlen(pbuffers[fd]) - ft_strlen(rest));
	if (!ft_strlen(rest))
	{
		free(rest);
		rest = 0;
	}
	free(pbuffers[fd]);
	pbuffers[fd] = rest;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*pbuffers[MAX_FDS];
	char		*temp;

	if (fd < 0 || fd > MAX_FDS || BUFFER_SIZE <= 0)
		return (0);
	if (!pbuffers[fd] && !readffd(fd, pbuffers))
		return (0);
	while (!ft_strchr(pbuffers[fd], '\n') && readffd(fd, pbuffers))
		;
	if (ft_strchr(pbuffers[fd], '\n'))
		temp = ft_split_next_line(fd, pbuffers);
	else
	{
		temp = ft_substr(pbuffers[fd], 0, ft_strlen(pbuffers[fd]));
		free(pbuffers[fd]);
		pbuffers[fd] = 0;
	}
	return (temp);
}
