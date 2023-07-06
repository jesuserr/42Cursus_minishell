/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:10:41 by jesuserr          #+#    #+#             */
/*   Updated: 2023/05/15 19:14:54 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*total_free(char **ptr1, char **ptr2, int flag)
{
	free (*ptr1);
	*ptr1 = NULL;
	if (flag == 1 && *ptr2)
	{
		free (*ptr2);
		*ptr2 = NULL;
	}
	return (NULL);
}

static void	*gnl_calloc(size_t count, size_t size)
{
	void	*ptr;
	void	*copy;
	size_t	len;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	len = count * size;
	copy = ptr;
	while (len > 0)
	{
		*(unsigned char *)(ptr) = 0;
		ptr++;
		len--;
	}	
	return (copy);
}

static char	*read_file(char *storage, int fd, int *bytes)
{
	char	*buffer;
	char	*backup_storage;

	buffer = (char *)gnl_calloc (sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (total_free(&storage, &storage, 0));
	*bytes = read (fd, buffer, BUFFER_SIZE);
	if (*bytes == -1 || (*bytes == 0 && !storage)
		|| (buffer[0] == '\0' && storage[0] == '\0'))
		return (total_free(&buffer, &storage, 1));
	backup_storage = storage;
	if (!storage)
		storage = gnl_strjoin ("", buffer, 0);
	else
		storage = gnl_strjoin (storage, buffer, 1);
	if (!storage)
		return (total_free(&buffer, &backup_storage, 1));
	total_free(&buffer, &buffer, 0);
	return (storage);
}

static char	*read_line(char **storage, int last_line)
{
	char		*backup_storage;
	char		*line;
	int			length;

	if (last_line == 0)
		length = gnl_strchr (*storage, '\n') + 1 - *storage;
	else
		length = gnl_strlen (*storage);
	line = gnl_substr (*storage, 0, length, 0);
	if (!line)
		return (total_free(storage, storage, 0));
	backup_storage = *storage;
	*storage = gnl_substr (*storage, length, gnl_strlen (*storage) - length, 1);
	if (!(*storage))
		return (total_free(&backup_storage, &backup_storage, 0));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage[FOPEN_MAX];
	int			bytes;
	int			last_line;

	last_line = 0;
	if (fd >= 0 && BUFFER_SIZE >= 1)
	{
		while (last_line == 0)
		{
			storage[fd] = read_file (storage[fd], fd, &bytes);
			if (!storage[fd])
				return (NULL);
			if (gnl_strchr (storage[fd], '\n'))
				return (read_line (&storage[fd], last_line));
			if (bytes < BUFFER_SIZE)
			{
				last_line = 1;
				return (read_line (&storage[fd], last_line));
			}		
		}
		return (total_free(&storage[fd], &storage[fd], 0));
	}
	return (NULL);
}
