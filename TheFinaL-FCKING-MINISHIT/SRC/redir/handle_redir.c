/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:18:18 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:19:32 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_infile(t_shell *shell, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		shell->exit_status = 1;
		return (1);
	}
	if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
		close(shell->fd_in);
	shell->fd_in = fd;
	return (0);
}

static int	open_outfile(t_shell *shell, const char *path, int flags)
{
	int	fd;
	int	backup;

	backup = -1;
	if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
	{
		backup = dup(shell->fd_out);
		close(shell->fd_out);
	}
	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		perror(path);
		shell->exit_status = 1;
		if (backup != -1)
			shell->fd_out = backup;
		else
			shell->fd_out = STDOUT_FILENO;
		return (1);
	}
	if (backup != -1)
		close(backup);
	shell->fd_out = fd;
	return (0);
}

int	handle_redirect_in(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	if (open_infile(shell, argv[1]) != 0)
		return (1);
	return (0);
}

int	handle_redirect_out(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	if (open_outfile(shell, argv[1], O_CREAT | O_TRUNC | O_WRONLY) != 0)
		return (1);
	return (0);
}

int	handle_append(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	if (open_outfile(shell, argv[1], O_CREAT | O_APPEND | O_WRONLY) != 0)
		return (1);
	return (0);
}
