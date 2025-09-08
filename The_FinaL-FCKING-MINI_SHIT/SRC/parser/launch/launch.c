/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkief <nkief@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/06 19:05:27 by nkief            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

int	check_pipe(t_exec_ctx *exc_context)
{
	if (exc_context->i < exc_context->sh->n_cmd - 1)
	{
		if (pipe(exc_context->pipe_fd) < 0)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

void	init_exec_ctx(t_exec_ctx *exc_context, t_shell *shell)
{
	exc_context->sh = shell;
	exc_context->node = shell->cmd_head;
	exc_context->i = 0;
	exc_context->prev_fd = -1;
}

int	try_fork_and_run(t_exec_ctx *ctx)
{
	pid_t	pid;

	g_exit_status = -1;
	parent_signals();
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		child_signals();
		child_exec(ctx);
	}
	parent_after_fork(ctx, pid);
	return (0);
}

/* Helper: gère les sorties précoces (heredocs / builtin seul) */
int	preflight_or_early_return(t_shell *sh)
{
	term_restore(sh);
	if (prepare_heredocs(sh))
	{
		term_apply(sh);
		init_signals();
		return (1);
	}
	if (!run_single_builtin_if_alone(sh))
	{
		term_apply(sh);
		init_signals();
		return (1);
	}
	return (0);
}

void	launch_process(t_shell *shell)
{
	t_exec_ctx	c;

	if (preflight_or_early_return(shell))
		return ;
	init_exec_ctx(&c, shell);
	while (c.i < shell->n_cmd)
	{
		if (check_pipe(&c) >= 0)
			(void)try_fork_and_run(&c);
		c.i++;
	}
	wait_all_update_status(shell);
	term_apply(shell);
	init_signals();
	update_last_pid_env(shell);
}
