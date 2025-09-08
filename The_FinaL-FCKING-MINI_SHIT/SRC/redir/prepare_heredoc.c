/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:41:50 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:43:20 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	close_heredocs(t_shell *sh)
{
	t_list	*node;
	t_token	*tok;
	int		i;

	node = sh->cmd_head;
	while (node)
	{
		tok = (t_token *)node->content;
		i = 0;
		while (i < tok->r_count)
		{
			if (tok->r[i].type == R_HEREDOC && tok->r[i].hfd >= 0)
			{
				close(tok->r[i].hfd);
				tok->r[i].hfd = -1;
			}
			i++;
		}
		node = node->next;
	}
}

/* traite l'effet d'un fd de heredoc sur tok->r[i] + status global */
static int	handle_heredoc_result(t_shell *sh, t_token *tok, int i, int fd)
{
	tok->r[i].hfd = fd;
	if (fd < 0)
	{
		close_heredocs(sh);
		if (fd == -2)
			sh->exit_status = 130;
		else
			sh->exit_status = 1;
		return (1);
	}
	return (0);
}

/* si r[i] est un heredoc, le construit ; sinon ne fait rien.
renvoie 1 si erreur */
static int	process_redir_i(t_shell *sh, t_token *tok, int i)
{
	t_delim	d;
	int		fd;

	if (tok->r[i].type != R_HEREDOC)
		return (0);
	d = parse_delim(tok->r[i].raw);
	fd = build_heredoc_fd(d, sh);
	free(d.clean);
	return (handle_heredoc_result(sh, tok, i, fd));
}

/* parcourt les redirs d'un token et prépare les heredocs */
static int	process_token_heredocs(t_shell *sh, t_token *tok)
{
	int	i;

	i = 0;
	while (i < tok->r_count)
	{
		if (process_redir_i(sh, tok, i))
			return (1);
		i++;
	}
	return (0);
}

int	prepare_heredocs(t_shell *sh)
{
	t_list	*node;

	node = sh->cmd_head;
	while (node)
	{
		if (process_token_heredocs(sh, (t_token *)node->content))
			return (1);
		node = node->next;
	}
	return (0);
}
