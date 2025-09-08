/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:28:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/28 15:39:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	child_setup_fds(t_exec_ctx *exc_context)
{
	if (exc_context->prev_fd != -1)
	{
		if (dup2(exc_context->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(exc_context->prev_fd);
	}
	if (exc_context->i < exc_context->sh->n_cmd - 1)
	{
		if (dup2(exc_context->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(exc_context->pipe_fd[0]);
		close(exc_context->pipe_fd[1]);
	}
}

void	child_exec(t_exec_ctx *exc_context)
{
	t_token	*tok;
	t_cmd	tmp;

	child_setup_fds(exc_context);
	tok = (t_token *)exc_context->node->content;
	ft_bzero(&tmp, sizeof(t_cmd));
	tmp.r = tok->r;
	tmp.r_count = tok->r_count;
	if (apply_redirs_in_child(&tmp, exc_context->sh))
	{
		exit(exc_context->sh->exit_status);
	}
	execute_cmd(exc_context->sh, tok);
	exit(exc_context->sh->exit_status);
}

void	parent_after_fork(t_exec_ctx *exc_context, pid_t pid)
{
	exc_context->sh->pids[exc_context->i] = pid;
	if (exc_context->prev_fd != -1)
		close(exc_context->prev_fd);
	if (exc_context->i < exc_context->sh->n_cmd - 1)
	{
		close(exc_context->pipe_fd[1]);
		exc_context->prev_fd = exc_context->pipe_fd[0];
	}
	else
		exc_context->prev_fd = -1;
	exc_context->node = exc_context->node->next;
}
