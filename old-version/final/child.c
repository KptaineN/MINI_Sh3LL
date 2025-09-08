/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:23:05 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 5
void	one_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	sh->pipe_to_close[0] = -1;
	sh->pipe_to_close[1] = -1; 
	execution_button((char **)cmd->arr_content, sh);
}
// »»-----► Number of lines: 7
void	multi_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	dup2(all->prev_pipe[0], STDIN_FILENO);
	dup2(all->curr_pipe[1], STDOUT_FILENO);	
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	sh->pipe_to_close[0] = all->prev_pipe[0];
	sh->pipe_to_close[1] = all->curr_pipe[1]; 
	execution_button((char **)cmd->arr_content, sh);
}
// »»-----► Number of lines: 7
void	end_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	dup2(all->prev_pipe[0], STDIN_FILENO);
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	sh->pipe_to_close[0] = all->curr_pipe[0];
	sh->pipe_to_close[1] = -1; 
	execution_button((char **)cmd->arr_content, sh);
}
// »»-----► Number of lines: 12
bool paria_cmd(t_sh *sh)
{
	char *cmd = (char *)sh->cmd->arr_content[0]; 
	if (!ft_strncmp(cmd,"export",6) || !ft_strcmp(cmd,"cd") || !ft_strncmp(cmd,"unset",5))
	{
		sh->cmd->arr_content = pid_expansion(sh->cmd->arr_content, sh->env);
		if (execution_bcmd((char **)sh->cmd->arr_content, sh))
			return 1;	
		write(STDERR_FILENO, "minish : ", 10);
		write(STDERR_FILENO, sh->cmd->arr_content[0], ft_strlen(sh->cmd->arr_content[0]));
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return 1;
	}
	return 0;
}