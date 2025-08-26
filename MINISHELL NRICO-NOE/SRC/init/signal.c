/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:25:14 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/26 19:51:37 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
/* c le parent qui ignore le signal*/

void    parent_signals(void)
{
        struct sigaction        sa_int;
        struct sigaction        sa_quit;

        sigemptyset(&sa_int.sa_mask);
        sa_int.sa_handler = SIG_IGN; //&handle_sigint;
        sa_int.sa_flags = SA_RESTART;
        sigemptyset(&sa_quit.sa_mask);
        sa_quit.sa_handler = SIG_IGN;
        sa_quit.sa_flags = 0;
        sigaction(SIGINT, &sa_int, NULL);
        sigaction(SIGQUIT, &sa_quit, NULL);
}

void    child_signals(void)
{
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
}