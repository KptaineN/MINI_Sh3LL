/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/28 17:02:36 by nkiefer          ###   ########.fr       */
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

void	init_exec_ctx(t_exec_ctx *exc_context, t_shell *sh)
{
	exc_context->sh = sh;
	exc_context->node = sh->cmd_head;
	exc_context->i = 0;
	exc_context->prev_fd = -1;
}

int	try_fork_and_run(t_exec_ctx *c)
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
		child_exec(c);
	}
	parent_after_fork(c, pid);
	return (0);
}

void	launch_process(t_shell *sh)
{
	t_exec_ctx	c;

	if (run_single_builtin_if_alone(sh))
		return ;
	init_exec_ctx(&c, sh);
	while (c.i < sh->n_cmd)
	{
		if (check_pipe(&c) < 0)
			return ;
		if (try_fork_and_run(&c) < 0)
			return ;
		c.i++;
	}
	wait_all_update_status(sh);
	init_signals();
	update_last_pid_env(sh);
}
