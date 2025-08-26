/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:28:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/26 20:13:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

void	child_setup_fds(t_exec_ctx *c)
{
	if (c->prev_fd != -1)
	{
		if (dup2(c->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(c->prev_fd);
	}
	if (c->i < c->sh->n_cmd - 1)
	{
		if (dup2(c->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(c->pipe_fd[0]);
		close(c->pipe_fd[1]);
	}
}

void	child_exec(t_exec_ctx *c)
{
	t_token	*tok;
	t_cmd	tmp;

	child_setup_fds(c);
	tok = (t_token *)c->node->content;
	ft_bzero(&tmp, sizeof(t_cmd));
	tmp.r = tok->r;
	tmp.r_count = tok->r_count;
	if (apply_redirs_in_child(&tmp, c->sh))
		exit(1);
	execute_cmd(c->sh, tok);
	exit(1);
}

void	parent_after_fork(t_exec_ctx *c, pid_t pid)
{
	c->sh->pids[c->i] = pid;
	if (c->prev_fd != -1)
		close(c->prev_fd);
	if (c->i < c->sh->n_cmd - 1)
	{
		close(c->pipe_fd[1]);
		c->prev_fd = c->pipe_fd[0];
	}
	else
		c->prev_fd = -1;
	c->node = c->node->next;
}

void	wait_all_update_status(t_shell *sh)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < sh->n_cmd) //transofrmer waitpid en liste 
        {
            waitpid(sh->pids[i], &status, 0); //ajouter option WNOHANG si pb
            if (i == sh->n_cmd - 1)
            {
                    if (WIFEXITED(status))
                            sh->exit_status = WEXITSTATUS(status);
                    else if (WIFSIGNALED(status))
                    {
                        if (WTERMSIG(status) == SIGINT)
							write(1, "\n", 1);
                        else if (WTERMSIG(status) == SIGQUIT)
							write(1, "Quit (core dumped)\n", 19);
						sh->exit_status = 128 + WTERMSIG(status);
                    }
                } // ajouter controle des wait, nouveau wait pour ceux qui nont pas finis
                i++;
        }
}
