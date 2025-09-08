/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:13:36 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:21:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "launcher.h"

/*
** Applique le statut d'attente au shell, mémorise le 1er SIGINT/SIGQUIT,
** et met à jour exit_status/g_exit_status si le pid est le "last".
*/
static void	apply_wait_status(int status, pid_t pid, t_wait_ctx *c)
{
	int	sig;

	if (WIFEXITED(status))
	{
		if (pid == c->last)
			g_exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (!c->sig_seen && (sig == SIGINT || sig == SIGQUIT))
		{
			c->sig_seen = 1;
			c->sig_num = sig;
		}
		if (pid == c->last)
			g_exit_status = 128 + sig;
	}
	if (pid == c->last)
		c->sh->exit_status = g_exit_status;
}

/*
** Calcule le nombre de pids spawnés (>0) et récupère le dernier (last_out).
*/
static int	get_spawned_and_last(const pid_t *pids, int n_cmd, pid_t *last_out)
{
	int	spawned;
	int	i;

	*last_out = -1;
	spawned = 0;
	i = 0;
	while (i < n_cmd)
	{
		if (pids[i] > 0)
		{
			*last_out = pids[i];
			spawned++;
		}
		i++;
	}
	return (spawned);
}

/*
** Drain non-bloquant : récupère immédiatement les enfants déjà terminés.
*/
static int	drain_nonblocking(t_wait_ctx *c)
{
	int		reaped;
	int		status;
	pid_t	pid;

	reaped = 0;
	pid = waitpid(-1, &status, WNOHANG);
	while (pid > 0)
	{
		apply_wait_status(status, pid, c);
		reaped++;
		pid = waitpid(-1, &status, WNOHANG);
	}
	if (pid == -1 && errno != ECHILD && errno != EINTR)
		perror("waitpid");
	return (reaped);
}

/*
** Attente bloquante pour les enfants restants (gestion propre d'EINTR).
*/
static void	wait_blocking(int remaining, t_wait_ctx *c)
{
	int		status;
	pid_t	pid;

	while (remaining > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			if (errno != EINTR)
				break ;
		}
		else
		{
			apply_wait_status(status, pid, c);
			remaining--;
		}
	}
}

/*
** Attends tous les enfants du pipeline et met à jour les statuts.
*/
void	wait_all_update_status(t_shell *shell)
{
	t_wait_ctx	c;
	int			spawned;
	int			reaped;
	int			remaining;

	if (!shell || !shell->pids || shell->n_cmd <= 0)
		return ;
	c.sh = shell;
	c.last = -1;
	c.sig_seen = 0;
	c.sig_num = 0;
	spawned = get_spawned_and_last(shell->pids, shell->n_cmd, &c.last);
	if (spawned == 0)
		return ;
	reaped = drain_nonblocking(&c);
	remaining = spawned - reaped;
	wait_blocking(remaining, &c);
	if (c.sig_seen)
	{
		if (c.sig_num == SIGINT)
			write(2, "\n", 1);
		else if (c.sig_num == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
	}
	g_exit_status = shell->exit_status;
}
