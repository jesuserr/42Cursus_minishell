/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:51:12 by jesuserr          #+#    #+#             */
/*   Updated: 2023/02/24 12:43:20 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	void	*copy;

	if (dst == NULL && src == NULL)
		return (dst);
	copy = dst;
	while (n > 0)
	{
		*(unsigned char *)(dst) = *(unsigned char *)(src);
		dst++;
		src++;
		n--;
	}
	return (copy);
}

char	*gnl_strjoin(char *s1, char const *s2, int erase)
{
	char	*s3;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	s3 = (char *)malloc (((len_s1 + len_s2) + 1) * sizeof(*s3));
	if (s3 == NULL)
		return (0);
	gnl_memcpy (s3, s1, len_s1);
	gnl_memcpy (s3 + len_s1, s2, len_s2);
	*(s3 + len_s1 + len_s2) = '\0';
	if (erase == 1)
		free (s1);
	return (s3);
}

char	*gnl_substr(char *s, unsigned int start, size_t len, int erase)
{
	char	*sub;
	size_t	length_s;

	if (s == NULL)
		return (0);
	length_s = gnl_strlen(s);
	if (start > length_s)
	{
		sub = (char *)malloc (sizeof(*sub));
		if (sub == NULL)
			return (0);
		*sub = 0;
		return (sub);
	}
	if (len > (length_s - start))
		len = length_s - start;
	sub = (char *)malloc ((len + 1) * sizeof(*sub));
	if (sub == NULL)
		return (0);
	gnl_memcpy (sub, s + start, len);
	*(sub + len) = '\0';
	if (erase == 1)
		free (s);
	return (sub);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
