/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:59:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/31 19:06:43 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_signal(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) info;
	(void) context;
	ft_printf(1, "\b\b\033[K");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signals_init(t_global *gd)
{
	gd->sig_data.sa_sigaction = ft_process_signal;
	sigemptyset(&gd->sig_data.sa_mask);
	gd->sig_data.sa_flags = 0;
	sigaction(SIGINT, &gd->sig_data, 0);
	sigaction(SIGQUIT, &gd->sig_data, 0);
}
