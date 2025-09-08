/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/29 10:55:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

int	run_single_builtin_if_alone(t_shell *shell)
{
	t_list	*curr;
	char	**args;
	int		idx;
	int		(*handler)(t_shell *, char **);

	if (shell->n_cmd != 1)
		return (0);
	curr = shell->cmd_head;
	args = expand_cmd((t_token *)curr->content, shell->env);
	if (!args)
		return (0);
	idx = is_in_t_arr_str(shell->bcmd, args[0]);
	if (idx == -1)
	{
		free_tab(args);
		return (0);
	}
	handler = get_builtin_handler(shell->bcmd, idx);
	if (handler)
		shell->exit_status = handler(shell, args);
	free_tab(args);
	return (1);
}

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

void	launch_process(t_shell *shell)
{
	t_exec_ctx	context;

	if (run_single_builtin_if_alone(shell))
		return ;
	init_exec_ctx(&context, shell);
	while (context.i < shell->n_cmd)
	{
		if (check_pipe(&context) < 0)
			return ;
		if (try_fork_and_run(&context) < 0)
			return ;
		context.i++;
	}
	wait_all_update_status(shell);
	init_signals();
	update_last_pid_env(shell);
}
