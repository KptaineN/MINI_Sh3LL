/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/04 11:51:53 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	one_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	char	**cmd_line;
	cmd_line = expansion_partition_redirection(cmd, sh->env, sh->oper);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	execution_button(cmd_line, sh);
}

void	multi_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	char	**cmd_line;
	dup2(all->prev_pipe[0], STDIN_FILENO);
	dup2(all->curr_pipe[1], STDOUT_FILENO);
	cmd_line = expansion_partition_redirection(cmd, sh->env, sh->oper);
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	sh->pipe_to_close[0] = &all->prev_pipe[0];
	sh->pipe_to_close[1] = &all->curr_pipe[1]; 
	execution_button(cmd_line, sh);
}

void	end_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	char	**cmd_line;
	dup2(all->prev_pipe[0], STDIN_FILENO);
	cmd_line = expansion_partition_redirection(cmd, sh->env, sh->oper);
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	sh->pipe_to_close[0] = &all->curr_pipe[0];
	sh->pipe_to_close[1] = NULL; 
	execution_button(cmd_line, sh);
}
