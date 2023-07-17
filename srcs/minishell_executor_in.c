/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:36:42 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 20:38:47 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_add_fd(int fd, t_token *t)
{
	int	count;

	if (fd < 3)
		return ;
	count = 0;
	while (t->fd_to_close[count])
		count++;
	t->fd_to_close[count] = fd;
}

void	ft_executor_in_literal(t_list *lst)
{
	int		count;
	t_token	*token;
	int		p[2];

	while (lst)
	{
		token = lst->content;
		count = -1;
		while (++count < token->n_in_literal)
		{
			pipe(p);
			token->cmdin = p[0];
			ft_executor_add_fd(token->cmdin, token);
			write(p[1], token->in_literal[count],
				strlen(token->in_literal[count]));
			close (p[1]);
		}
		lst = lst->next;
	}
}

int	ft_executor_in_file(t_list *lst)
{
	int		count;
	t_token	*token;
	char	strerr[500];

	while (lst)
	{
		token = lst->content;
		count = -1;
		while (++count < token->n_in)
		{
			token->cmdin = open(token->in[count], O_RDONLY, 0444);
			if (token->cmdin > 0)
				ft_executor_add_fd(token->cmdin, token);
			else
			{
				token->cmdin = 0;
				sprintf(strerr, "%s: No such file or directory",
					token->in[count]);
				ft_error_shell(strerr);
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}

void	ft_executor_heredoc(t_list *lst)
{
	int		count;
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		count = -1;
		while (++count < token->n_heredoc)
		{
			token->cmdin = ft_heredoc(token->heredoc[count]);
			ft_executor_add_fd(token->cmdin, token);
		}
		lst = lst->next;
	}
}
