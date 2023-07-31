/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:59:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/31 22:08:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_signal(int sig, siginfo_t *info, void *context)
{
	t_list *lst;
	t_token *token;
	int	for_pid_status;

	(void) info;
	(void) context;
	lst = 0;
	if (sig == SIGINT && *g_info->cmds)
	{
		lst = **g_info->cmds;
		for_pid_status = 0;
		while (lst && !for_pid_status)
		{
			token = lst->content;
			for_pid_status = token->d->fork_pid;
			if (!token->d->fork_pid)
				lst = lst->next;
		}
	}
	if (lst)
	{
		kill(token->d->fork_pid, SIGINT);
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
	//dup2(g_info->copy_stdin, STDIN_FILENO);
	//dup2(g_info->copy_stdout, STDOUT_FILENO);
}

void	ft_signals_init(t_global *gd)
{
	gd->sig_data.sa_sigaction = ft_process_signal;
	sigemptyset(&gd->sig_data.sa_mask);
	gd->sig_data.sa_flags = 0;
	sigaction(SIGINT, &gd->sig_data, 0);
	sigaction(SIGQUIT, &gd->sig_data, 0);
}
