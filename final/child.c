/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:43 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/05 12:16:01 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"


void  **pid_expansion(void **v_arr, t_list *env)
{
	int n;
	int i= 0;
	char *p;
	char ** arr = (char **)v_arr;
	char *s_pid = get_env_value(env, "PID");
	int l_pid = ft_strlen(s_pid);
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
		}
		if (n != 0)
		{
			char *new = malloc((l_pid-2)*n+ft_strlen(arr[i])+1);

			char *s = arr[i];
			int idx = 0;
			while (1)
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
			}
			ft_strcpy(new+idx,s);
			new[idx+ft_strlen(s)] = 0;
			free(arr[i]);	
			arr[i] = new;
		}
		i++;
	}
	return v_arr;
}

void	one_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	cmd->arr_content = pid_expansion(cmd->arr_content, sh->env);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	execution_button((char **)cmd->arr_content, sh);
}

void	multi_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	dup2(all->prev_pipe[0], STDIN_FILENO);
	dup2(all->curr_pipe[1], STDOUT_FILENO);
	cmd->arr_content = pid_expansion(cmd->arr_content, sh->env);
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	sh->pipe_to_close[0] = &all->prev_pipe[0];
	sh->pipe_to_close[1] = &all->curr_pipe[1]; 
	execution_button((char **)cmd->arr_content, sh);
}

void	end_child(t_sh *sh, t_list *cmd, t_launch *all)
{
	dup2(all->prev_pipe[0], STDIN_FILENO);
	cmd->arr_content = pid_expansion(cmd->arr_content, sh->env);
	close(all->prev_pipe[1]);
	close(all->curr_pipe[0]);
	close(all->curr_pipe[1]);
	sh->pipe_to_close[0] = &all->curr_pipe[0];
	sh->pipe_to_close[1] = NULL; 
	execution_button((char **)cmd->arr_content, sh);
}
