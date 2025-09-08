/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:41 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:24:43 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include <errno.h>

/* ouvre après expansion ; -2 si ambiguous, -1 si open fail, fd sinon */
int	open_from_expansion(t_redir *r, t_shell *sh, int flags, int mode)
{
	char	*file;
	int		fd;
	int		err;

	file = expand_filename_if_needed(r->raw, sh);
	if (is_ambiguous(file, r->quoted))
	{
		ambiguous(r->raw);
		free(file);
		return (-2);
	}
	fd = open(file, flags, mode);
	err = errno;
	free(file);
	if (fd < 0)
	{
		errno = err;
		return (-1);
	}
	return (fd);
}

int	open_and_dup_in(t_redir *r, t_shell *sh)
{
	int	fd;
	int	err;

	fd = open_from_expansion(r, sh, O_RDONLY, 0);
	if (fd == -2)
	{
		sh->exit_status = 1;
		return (1);
	}
	if (fd < 0)
	{
		err = errno;
		ft_putstr_fd(r->raw, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(err), STDERR_FILENO);
		if (err == ENOENT || err == EACCES)
			sh->exit_status = 1;
		else
			sh->exit_status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	open_and_dup_out_trunc(t_redir *r, t_shell *sh)
{
	int	fd;
	int	err;

	fd = open_from_expansion(r, sh, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -2)
	{
		sh->exit_status = 1;
		return (1);
	}
	if (fd < 0)
	{
		err = errno;
		ft_putstr_fd(r->raw, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(err), STDERR_FILENO);
		if (err == ENOENT || err == EACCES)
			sh->exit_status = 1;
		else
			sh->exit_status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	open_and_dup_out_append(t_redir *r, t_shell *sh)
{
	int	fd;
	int	err;

	fd = open_from_expansion(r, sh, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -2)
	{
		sh->exit_status = 1;
		return (1);
	}
	if (fd < 0)
	{
		err = errno;
		ft_putstr_fd(r->raw, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(err), STDERR_FILENO);
		if (err == ENOENT || err == EACCES)
			sh->exit_status = 1;
		else
			sh->exit_status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
