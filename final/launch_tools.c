/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:48:34 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:52:55 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 4
void add_pid(t_sh *sh, const char *key, int fd[2])
{
    char s[20];
    ssize_t n = read(fd[0], s,sizeof(s));
    if (n >= 0)
    {
        s[n] = 0;
        replace_or_add(&sh->env, key, (const char *)s);
    }
    close(fd[1]);
	close(fd[0]);
}
// »»-----► Number of lines: 4
void send_pid(int fd[2], int pid)
{
    char *s_pid = ft_itoa(pid);
    write(fd[1], s_pid, ft_strlen(s_pid));  // Send child's PID to child
    write(fd[1],"\0",1);
    free(s_pid);
    close(fd[1]);
	close(fd[0]);
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
}