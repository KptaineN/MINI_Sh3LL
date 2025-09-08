/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:29:01 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:03:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Dépendances supposées :
** - toggle_quotes(char c, bool *in_sq, bool *in_dq)
** - ft_putstr_fd, ft_strlen, ft_strjoin, free, readline
** - g_exit_status (extern int)
*/
void	quote_scan_from(const char *s, size_t *i, bool *in_sq, bool *in_dq)
{
	while (s[*i])
		toggle_quotes(s[(*i)++], in_sq, in_dq);
}

static int	on_unmatched_eof(void)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n",
		STDERR_FILENO);
	return (-1);
}

static int	append_and_free(char **dst, char *owned_suffix)
{
	char	*joined;

	joined = ft_strjoin(*dst, owned_suffix);
	if (!joined)
	{
		free(owned_suffix);
		return (-1);
	}
	free(*dst);
	free(owned_suffix);
	*dst = joined;
	return (0);
}

static int	append_const(char **dst, const char *suffix)
{
	char	*joined;

	joined = ft_strjoin(*dst, suffix);
	if (!joined)
		return (-1);
	free(*dst);
	*dst = joined;
	return (0);
}

int	read_line_step(char **in, size_t *i, bool *in_sq, bool *in_dq)
{
	char	*next;
	size_t	old_len;

	next = readline("> ");
	if (!next)
		return (on_unmatched_eof());
	if (g_exit_status == 130)
	{
		free(next);
		return (-2);
	}
	old_len = ft_strlen(*in);
	if (append_and_free(in, next) == -1)
		return (-1);
	*i = old_len;
	quote_scan_from(*in, i, in_sq, in_dq);
	if (*in_sq || *in_dq)
		if (append_const(in, "\n") == -1)
			return (-1);
	return (0);
}
