/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:59:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/08/01 13:55:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_signal_int2(t_list *lst, int fork_pid)
{
	if (lst)
	{
		kill(fork_pid, SIGINT);
		ft_printf(1, "\n");
	}
	else
	{
		ft_printf(1, "\b\b\033[K");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_process_signal_int(int sig)
{
	t_list	*lst;
	t_token	*token;
	int		fork_pid;

	(void) sig;
	lst = 0;
	token = 0;
	fork_pid = 0;
	if (*g_info->cmds)
	{
		lst = **g_info->cmds;
		while (lst && !fork_pid)
		{
			token = lst->content;
			fork_pid = token->d->fork_pid;
			if (!token->d->fork_pid)
				lst = lst->next;
		}
	}
	ft_process_signal_int2(lst, fork_pid);
	if (dup2(g_info->copy_stdin, STDIN_FILENO) == -1
		|| dup2(g_info->copy_stdout, STDOUT_FILENO) == -1)
		ft_error_shell("dup2: bad file descriptor");
	g_info->last_status = 130;
}

void	ft_process_signal_quit2(t_list *lst)
{
	if (!lst)
	{
		ft_printf(1, "\b\b\033[K");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		ft_printf(1, "Quit: 3\n");
	}
}

void	ft_process_signal_quit(int sig)
{
	t_list	*lst;
	t_token	*token;
	int		fork_pid;

	(void) sig;
	lst = 0;
	token = 0;
	fork_pid = 0;
	if (*g_info->cmds)
	{
		lst = **g_info->cmds;
		while (lst && !fork_pid)
		{
			token = lst->content;
			fork_pid = token->d->fork_pid;
			if (!token->d->fork_pid)
				lst = lst->next;
		}
	}
	ft_process_signal_quit2(lst);
	if (dup2(g_info->copy_stdin, STDIN_FILENO) == -1
		|| dup2(g_info->copy_stdout, STDOUT_FILENO) == -1)
		ft_error_shell("dup2: bad file descriptor");
	g_info->last_status = 131;
}

void	ft_signals_init(void)
{
	signal(SIGINT, ft_process_signal_int);
	signal(SIGQUIT, ft_process_signal_quit);
}
