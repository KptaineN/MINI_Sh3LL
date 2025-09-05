/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:28:54 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/05 12:26:04 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	init_pip(t_sh *sh, t_launch *all)
{
	all->pids = malloc(sizeof(int) * sh->n_cmd);
	if (!all->pids)
		return 1;
	all->prev_pipe[0] = -1;
	all->prev_pipe[1] = -1;
	return 0;
}


void	ctrl_c(int sig)
{
	write(1,"\n",1);
	(void)sig;
}

void	back_slash(int sig)
{
	printf("Quit (core dumped)\n");
	(void)sig;
}

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
		add_env(sh, "PID=",all->fd_pid[0]);
		close(all->fd_pid[1]);
		close(all->fd_pid[0]);
		(f[0])(sh, sh->cmd, all);
	}
	else
	{	
        send_pid(all->fd_pid[1], *all->pid);
        close(all->fd_pid[1]);
		close(all->fd_pid[0]);
		(f[1])(sh, sh->cmd, all);
    }
}

typedef enum e_condition
{
	ONE_CMD_FUNCTION,
	MULTI_CMD_FUNCTION,
	END_CMD_FUNCTION
}	t_condition;

void condition_dual_funciton_repartition(t_sh *sh, t_launch *all)
{
	if (sh->n_cmd == 1)
		separate_family(sh->f_core[ONE_CMD_FUNCTION], sh, all);
	else if (*all->idx != sh->n_cmd - 1)
		separate_family(sh->f_core[MULTI_CMD_FUNCTION], sh, all);
	else
		separate_family(sh->f_core[END_CMD_FUNCTION], sh, all);
}



void execution_bcmd( char **cmd_line, t_sh *sh)
{
	int idx;
	idx = is_in_t_arr_dic_str(sh->bcmd, cmd_line[0]);
	if (idx != -1)
	{
		t_dic *dic = (t_dic *)sh->bcmd->arr[idx];
		void (*func)(t_sh *, char **) = dic->value;
		func(sh, cmd_line);
		exit(1);
	}
}

void	execution_button(char **cmd_line, t_sh *sh)
{
	char *path = find_command_path(cmd_line[0], sh->env);

	if (access(path, X_OK) == -1)
	{
		execution_bcmd(cmd_line, sh);
		free_string_array(cmd_line);
		perror("access");
		exit(1);
	}
	if (cmd_line)
		execv(path, cmd_line);
	perror("execv");
	exit(1);
}

void wait_all_pids(int **pids, int n)
{
	int i;
	i = 0;
	int status = 0;
	while (i < n)
	{
		waitpid((*pids)[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status)) {
		g_exit_status = WEXITSTATUS(status);
	} else if (WIFSIGNALED(status)) {
		g_exit_status = 128 + WTERMSIG(status);
    }
	free(*pids);
	*pids = NULL;
}

int pipe_and_fork(t_launch *all, int i)
{
	if (pipe(all->fd_pid) == -1 || pipe(all->curr_pipe) == -1)
	{
		perror("pipe");
		return 1;
	}
	all->pids[i] = fork();
	all->pid = &all->pids[i];
	return 0;
}

void	launch_process(t_sh *sh)
{
	int i;
	t_launch all;
	i = 0;
	all.idx = &i;
	init_pip(sh, &all);
	while (sh->cmd != NULL && i < sh->n_cmd)
	{
		if (pipe_and_fork(&all, i))
			exit(1);
		condition_dual_funciton_repartition(sh, &all);
		advance_node(&sh->cmd);
		i++;
	}
	wait_all_pids(&all.pids, sh->n_cmd);
}
