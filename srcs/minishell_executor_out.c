/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_out.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:33:07 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/17 21:50:28 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_out_file_error(t_token *t, char *out)
{
	char	strerr[500];

	t->cmdout = 1;
	sprintf(strerr, "%s: Permission denied", out);
	ft_error_shell(strerr);
}

int	ft_executor_out_file(t_list *lst)
{
	int		count;
	t_token	*t;

	while (lst)
	{
		t = lst->content;
		count = -1;
		while (++count < t->n_out)
		{
			t->cmdout = open(t->out[count],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (t->cmdout > 1)
				ft_executor_add_fd(t->cmdout, t);
			else
			{
				ft_executor_out_file_error(t, t->out[count]);
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}

int	ft_executor_out_file_add(t_list *lst)
{
	int		count;
	t_token	*t;

	while (lst)
	{
		t = lst->content;
		count = -1;
		while (++count < t->n_out_add)
		{
			t->cmdout = open(t->out_add[count],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (t->cmdout > 1)
				ft_executor_add_fd(t->cmdout, t);
			else
			{
				ft_executor_out_file_error(t, t->out_add[count]);
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}
