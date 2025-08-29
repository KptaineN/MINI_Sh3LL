/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:32:55 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/26 19:09:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	open_pipe_if_needed(int has_next, int pipe_fd[2])
{
	if (!has_next)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		return (0);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	close_if_valid(int fd)
{
	if (fd != -1)
		close(fd);
}

static void	set_exit_from_status(t_shell *sh, int status)
{
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_status = 128 + WTERMSIG(status);
}

void	wait_pipeline(t_shell *sh, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(sh->pids[i], &status, 0);
		if (i == count - 1)
			set_exit_from_status(sh, status);
		i++;
	}
	//restore_ssignals();
}
