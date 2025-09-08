/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:25:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:43:51 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* Copie raw sans guillemets dans d->clean et met d->quoted = 1 si trouvé.
   Retourne 1 si OK, 0 si malloc fail. */
static int	copy_no_quotes(t_delim *d, const char *raw)
{
	size_t	i;
	size_t	j;
	char	*clean;

	clean = malloc(ft_strlen(raw) + 1);
	if (!clean)
		return (1);
	i = 0;
	j = 0;
	while (raw[i])
	{
		if (raw[i] == '\'' || raw[i] == '\"')
		{
			d->quoted = 1;
			i++;
		}
		else
			clean[j++] = raw[i++];
	}
	clean[j] = '\0';
	d->clean = clean;
	return (0);
}

t_delim	parse_delim(const char *raw)
{
	t_delim	d;

	d.raw = (char *)raw;
	d.clean = NULL;
	d.quoted = 0;
	if (!raw)
		return (d);
	if (copy_no_quotes(&d, raw))
		return (d);
	return (d);
}

static int	apply_one_redir(t_redir *r, t_shell *sh)
{
	if (r->type == R_IN)
		return (open_and_dup_in(r, sh));
	if (r->type == R_OUT_TRUNC)
		return (open_and_dup_out_trunc(r, sh));
	if (r->type == R_OUT_APPEND)
		return (open_and_dup_out_append(r, sh));
	if (r->type == R_HEREDOC)
	{
		dup2(r->hfd, STDIN_FILENO);
		close(r->hfd);
		r->hfd = -1;
		return (0);
	}
	return (0);
}

static void	close_remaining_heredocs(t_cmd *c, int start)
{
	int	j;

	j = start;
	while (j < c->r_count)
	{
		if (c->r[j].type == R_HEREDOC && c->r[j].hfd >= 0)
		{
			close(c->r[j].hfd);
			c->r[j].hfd = -1;
		}
		j++;
	}
}

int	apply_redirs_in_child(t_cmd *c, t_shell *sh)
{
	int	ret;
	int	i;

	i = 0;
	while (i < c->r_count)
	{
		ret = apply_one_redir(&c->r[i], sh);
		if (ret != 0)
		{
			close_remaining_heredocs(c, i);
			if (sh->exit_status == 0)
				sh->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
