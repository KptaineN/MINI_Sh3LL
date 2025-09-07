/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:28:54 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 14:16:05 by eganassi         ###   ########.fr       */
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
void	ctrl_c(int sig)
{
	write(1,"\n",1);
	(void)sig;
}
// »»-----► Number of lines: 2
void	back_slash(int sig)
{
	printf("Quit (core dumped)\n");
	(void)sig;
}
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
		sh->cmd->arr_content = pid_expansion(sh->cmd->arr_content, sh->env);
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
// »»-----► Number of lines: 4
{
	ONE_CMD_FUNCTION,
	MULTI_CMD_FUNCTION,
	END_CMD_FUNCTION
}	t_condition;
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
// »»-----► Number of lines: 10
int execution_bcmd( char **cmd_line, t_sh *sh)
{
	int idx;
	idx = is_in_t_arr_dic_str(sh->bcmd, cmd_line[0]);
	if (idx != -1)
	{
		t_dic *dic = (t_dic *)sh->bcmd->arr[idx];
		void (*func)(t_sh *, char **) = dic->value;
		func(sh, cmd_line);
		return 1;
	}
	return 0;
}

//return overall length and return the pointer of n_redir
// »»-----► Number of lines: 10
void count_redir(t_arr *oper,char **arr, int *len,int *n_redir)
{
	*n_redir = 0;
	*len = 0;
	while(arr[*len])
	{
		if (is_in_t_arr_dic_str(oper,arr[(*len)++]) != -1)
		{	
			(*len)++;
			(*n_redir)++;
		}
	}
}

typedef struct s_redir
{
	int n_redir; 
// »»-----► Number of lines: 16
	int len;
	char **new; 
	int i;
	int j;
	int idx_oper;
	t_func f;
}	t_redir;

//rebuild_cmd_without_redir_and_apply_them
char **rebuild_noredir_cmd(t_arr *oper, char **arr, int *pipe)
{
	t_redir r;
	ft_bzero(&r, sizeof(t_redir));
	count_redir(oper, arr, &r.len, &r.n_redir);
	r.new = malloc(sizeof(char*)*(r.len - 2*r.n_redir+1));
	while(arr[r.i])
	{
		r.idx_oper = is_in_t_arr_dic_str(oper,arr[r.i]);
		if (r.idx_oper!=-1)
		{
			r.f = (t_func)((t_dic *)oper->arr[r.idx_oper])->value;
			free(arr[r.i++]);
			r.f((void *)arr[r.i], (void **)arr, pipe);
			free(arr[r.i++]);
		}
		else
			r.new[r.j++] = arr[r.i++];
	}
	free(arr);
	r.new[r.j] = NULL;
	return r.new;
}

// »»-----► Number of lines: 16
void	execution_button(char **cmd_line, t_sh *sh)
{
	char *path = find_command_path(cmd_line[0], sh->env);
	cmd_line = rebuild_noredir_cmd(sh->oper, cmd_line, (int *)sh->pipe_to_close);
	if (path == NULL)
	{
		if (execution_bcmd(cmd_line, sh))
			exit(0);
		write(STDERR_FILENO, "minish : ", 10);
		write(STDERR_FILENO, cmd_line[0], ft_strlen(cmd_line[0]));
		ft_putendl_fd(": command not found", STDERR_FILENO);
		free_string_array(cmd_line);
		exit(127);
	}
// »»-----► Number of lines: 8
	else if (access(path, X_OK) == 0)
		execv(path, cmd_line);
	exit(0);
}
// »»-----► Number of lines: 12
void wait_all_pids(int **pids, int n)
{
	int i;
	i = 0;
	int status = 0;
	while (i < n)
	{
		if ((*pids)[i] != -1)
			waitpid((*pids)[i], &status, 0);
		i++;
	}
	g_exit_status = assign_signal(status);
	free(*pids);
	*pids = NULL;
// »»-----► Number of lines: 4
}
// »»-----► Number of lines: 8
int pipe_and_fork(t_launch *all, int i)
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
	if (sh->n_cmd == 1 && paria(sh))
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
