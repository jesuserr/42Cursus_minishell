/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:59:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/07/28 22:08:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process_signal(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) info;
	(void) context;
	rl_replace_line("", 0);
	ft_printf(1, "\b\b\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signals_init(t_global *gd)
{
	gd->sig_data.sa_sigaction = ft_process_signal;
	sigemptyset(&gd->sig_data.sa_mask);
	gd->sig_data.sa_flags = 0;
	sigaction(SIGINT, &gd->sig_data, 0);
}