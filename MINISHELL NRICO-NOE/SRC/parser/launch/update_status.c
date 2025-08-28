/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:13:36 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/28 17:04:44 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_status_from_wait(int status, t_shell *shell)
{
	int	signal;

	signal = 0;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			write(2, "\n", 1);
		else if (signal == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		shell->exit_status = 128 + signal;
	}
}

static void	remaining_children(int remaining, pid_t last, t_shell *sh)
{
	int		status;
	pid_t	pid;
	int		interrupted;

	while (remaining > 0)
	{
		interrupted = 0;
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			if (errno == EINTR)
				interrupted = 1;
			else if (errno == ECHILD)
				break ;
			else
				break ;
		}
		if (!interrupted)
		{
			if (pid == last)
				set_status_from_wait(status, sh);
			remaining--;
		}
	}
}

/*
 * Attends TOUS les enfants.
 * - Draine d'abord en non-bloquant (WNOHANG) si certains sont déjà morts.
 * - Termine en bloquant jusqu'à avoir tout récupéré.
 * - Met à jour sh->exit_status avec le statut du DERNIER process du pipeline.
 */
static int	get_spawned_and_last(const pid_t *pids, int n_cmd, pid_t *last_out)
{
	int	spawned;
	int	k;

	*last_out = -1;
	spawned = 0;
	k = 0;
	while (k < n_cmd)
	{
		if (pids[k] > 0)
		{
			*last_out = pids[k];
			spawned++;
		}
		k++;
	}
	return (spawned);
}

/* 2) Drain non-bloquant: récupère les enfants déjà terminés,
	met à jour le statut si c'est "last" */
static int	drain_nonblocking(pid_t last, t_shell *shell)
{
	int		reaped;
	int		status;
	pid_t	pid;

	reaped = 0;
	pid = waitpid(-1, &status, WNOHANG);
	while (pid > 0)
	{
		if (pid == last)
			set_status_from_wait(status, shell);
		reaped++;
		pid = waitpid(-1, &status, WNOHANG);
	}
	if (pid == -1 && errno != ECHILD && errno != EINTR)
		perror("waitpid");
	return (reaped);
}

void	wait_all_update_status(t_shell *shell)
{
	pid_t	last;
	int		reaped;
	int		remaining;
	int		spawned;

	spawned = 0;
	if (!shell || !shell->pids || shell->n_cmd <= 0)
	{
		return ;
	}
	spawned = get_spawned_and_last(shell->pids, shell->n_cmd, &last);
	if (spawned == 0)
	{
		return ;
	}
	reaped = drain_nonblocking(last, shell);
	remaining = spawned - reaped;
	remaining_children(remaining, last, shell);
}
