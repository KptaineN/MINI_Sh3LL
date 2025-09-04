/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:01:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/01 14:01:18 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(2, "\n", 1); // stderr
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

void	init_family(t_sh *sh)
{
	int i = 0;
	t_family f[][2] = { {one_child, one_parent}, 
		                {multi_child, multi_parent}, 
                        {end_child, end_parent},
                        {NULL, NULL} };
	sh->f_core = malloc(sizeof(t_family *) * 5);
	int len = sizeof(f) / sizeof(f[0])-1;
	while (i < len)
	{
		sh->f_core[i] = malloc(sizeof(t_family) * 2);	
		sh->f_core[i][0] = f[i][0];
		sh->f_core[i][1] = f[i][1];
		i++;
	}
	sh->f_core[len] = NULL;
}

int	start_sh(t_sh *sh)
{	
	if (!sh)
		return (1);
	init_signals();
	return (0);
}

void	init_sh(t_sh *sh, char **envp)
{
	sh->env = set_linked_env(envp);
    init_all_t_arr(sh);
	init_family(sh);
	start_sh(sh);
}