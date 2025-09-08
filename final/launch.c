/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:28:54 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 13:15:08 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 6
static int	init_pip(t_sh *sh, t_launch *all)
{
	all->pids = malloc(sizeof(int) * sh->n_cmd);
	if (!all->pids)
		return 1;
	all->prev_pipe[0] = -1;
	all->prev_pipe[1] = -1;
	return 0;
}
// »»-----► Number of lines: 2

// »»-----► Number of lines: 22
static void	separate_family(t_family *f, t_sh *sh, t_launch *all)
{
	if (*all->pid < 0)
	{
		perror("Forks");
		exit(1);
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, back_slash);
	if (*all->pid == 0)
	{
		add_pid(sh, "PID",all->fd_pid);
		sh->cmd->arr_content = pid_expansion(sh->cmd->arr_content, sh->env);
		(f[0])(sh, sh->cmd, all);
	}
	else
	{	
        send_pid(all->fd_pid, *all->pid);
		(f[1])(sh, sh->cmd, all);
    }
}
// »»-----► Number of lines: 6
void condition_dual_funciton_repartition(t_sh *sh, t_launch *all)
{
	if (sh->n_cmd == 1)
		separate_family(sh->f_core[ONE_CMD_FUNCTION], sh, all);
	else if (*all->idx != sh->n_cmd - 1)
		separate_family(sh->f_core[MULTI_CMD_FUNCTION], sh, all);
	else
		separate_family(sh->f_core[END_CMD_FUNCTION], sh, all);
}
// »»-----► Number of lines: 8
static int pipe_and_fork(t_launch *all, int i)
{
	if (pipe(all->fd_pid) == -1 || pipe(all->curr_pipe) == -1)
	{
		perror("pipe");
		return 1;
	}
	all->pids[i] = fork();
// »»-----► Number of lines: 17
	all->pid = &all->pids[i];
	return 0;
}
// »»-----► Number of lines: 20
void	launch_process(t_sh *sh)
{
	int i;
	t_launch all;
	if (sh->n_parsed == 0)
		return;
	if (sh->n_cmd == 1 && paria_cmd(sh))
		return;
	t_list *remember = sh->cmd;
	i = 0;
	all.idx = &i;
	init_pip(sh, &all);
	while (sh->cmd != NULL && i < sh->n_cmd)
	{
		if (pipe_and_fork(&all, i))
			exit(1);
		condition_dual_funciton_repartition(sh, &all);
		sh->cmd = sh->cmd->next;
		i++;
	}
	wait_all_pids(&all.pids, sh->n_cmd);
	sh->cmd = remember;
}
