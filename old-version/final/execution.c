/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:54:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:20:33 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minish.h"
// »»-----► Number of lines: 10
static void count_redir(t_arr *oper,char **arr, int *len,int *n_redir)
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
// »»-----► Number of lines: 20
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
// »»-----► Number of lines: 15
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
	else if (access(path, X_OK) == 0)
		execv(path, cmd_line);
	exit(0);
}