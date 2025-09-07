/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 14:12:48 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 49
void  **pid_expansion(void **v_arr, t_list *env)
{
	int n;
	int i= 0;
	char *p;
	char ** arr = (char **)v_arr;
	
	while(arr[i])
	{
		n = 0;
		p = arr[i];
		while(1)
		{
			p = ft_strchr(p,'$');
			if (!p)
				break;
			if (*(p+1) == '$')
			{	
				p+=2;
				n++;
			}
			else if (!*(p+1))
				break;
			else
				p++;
		}
		if (n != 0)
		{
			
			char *s_pid = get_env_value(env, "PID");
			int l_pid = ft_strlen(s_pid);
			int len = (l_pid-2)*n+ft_strlen(arr[i]);
			char *new = malloc(len+1);

			char *s = arr[i];
			int idx = 0;
			while (*s)
			{
				p = ft_strchr(s,'$');
				if (!p)
					break;
				if (*(p+1) == '$')
				{
					ft_strncpy(new+idx,s,(unsigned int)(p-s));
					idx = (unsigned int)(p-s);
					ft_strcpy(new+idx,s_pid);
					idx+=l_pid;
					s = p+2;
				}
				else
					s = p+1;
			}
			ft_strcpy(new+idx,s);
			new[len] = 0;
			free(arr[i]);	
			arr[i] = new;
		}
		i++;
	}
	return v_arr;
}
// »»-----► Number of lines: 4
void	one_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	sh->pipe_to_close[0] = -1;
	sh->pipe_to_close[1] = -1; 
	execution_button((char **)cmd->arr_content, sh);
}
// »»-----► Number of lines: 8
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
// »»-----► Number of lines: 8
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

bool paria(t_sh *sh)
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