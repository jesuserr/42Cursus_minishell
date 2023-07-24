/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:04:27 by jesuserr          #+#    #+#             */
/*   Updated: 2023/07/24 19:13:55 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Allows to free at the same time a double pointer (typically from ft_split) */
/* and optionally a single pointer, if provided */
/* Returns ** '0' after completion, only used by '**copy_dbl_char_pointer' to */
/* exit with a NULL and respect 25 lines limit */
char	**free_split(char **str_1, char *str_2)
{
	size_t	i;

	if (str_2)
		free(str_2);
	i = 0;
	while (str_1 && str_1[i])
		free(str_1[i++]);
	free(str_1);
	return (0);
}

/* Makes copy of double char pointer, if something goes wrong returns NULL  */
char	**copy_dbl_char_pointer(char **src)
{
	int		i;
	int		j;
	int		len;
	char	**dst;

	if (!src)
		return (NULL);
	j = 0;
	while (src[j])
		j++;
	dst = (char **)malloc(sizeof(char *) * (j + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < j)
	{
		len = ft_strlen(src[i]);
		dst[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!dst[i])
			return (free_split(dst, NULL));
		ft_strlcpy(dst[i], src[i], len + 1);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

/* Verifies if a string is just made of blanks/tabs/feeds */
int	check_empty_string(char *str)
{
	if (!str)
		return (-1);
	while (*str != '\0')
	{
		if (*str != ' ' && !(*str >= '\t' && *str <= '\r'))
			return (0);
		str++;
	}
	return (-1);
}

/* Counts the number of lines of a double char pointer */
int	count_dbl_char_lines(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/* Allows to free two pointers at once, main purpose is saving lines of code */
void	double_free(char *str_1, char *str_2)
{
	if (str_1)
		free(str_1);
	if (str_2)
		free(str_2);	
}