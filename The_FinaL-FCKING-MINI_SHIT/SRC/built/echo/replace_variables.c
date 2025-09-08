/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:29:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:27:54 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "../../../include/minishell.h"

static void	rv_emit_char(t_rv *st)
{
	if (st->out)
		st->out[st->j] = st->a[st->i];
	st->i++;
	st->j++;
}

static void	rv_handle_dollar(t_rv *st)
{
	char	*dst;
	int		idx;

	dst = NULL;
	if (st->out)
		dst = &st->out[st->j];
	idx = (int)st->i;
	st->j += process_dollar(dst, st->a, &idx, st->sh);
	st->i = (size_t)idx;
}

static void	rv_handle_escape(t_rv *st)
{
	if (!st->a[st->i + 1])
	{
		if (st->out)
			st->out[st->j] = '\\';
		st->i++;
		st->j++;
		return ;
	}
	if (st->out)
		st->out[st->j] = st->a[st->i + 1];
	st->i += 2;
	st->j++;
}

static size_t	rv_walk(t_rv *st)
{
	rv_reset(st);
	while (st->a[st->i])
	{
		update_quotes(st->a, st->i, &st->sq, &st->dq);
		if (!st->sq && st->a[st->i] == '\\' && escape_check(st->a, st->i))
			rv_handle_escape(st);
		else if (st->a[st->i] == '$' && !st->sq && escape_check(st->a, st->i))
			rv_handle_dollar(st);
		else
			rv_emit_char(st);
	}
	if (st->out)
		st->out[st->j] = '\0';
	return (st->j);
}

char	*replace_variables(const char *arg, t_shell *sh)
{
	t_rv	st;
	size_t	len;
	char	*res;

	st.a = arg;
	st.sh = sh;
	st.out = NULL;
	len = rv_walk(&st);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	st.out = res;
	rv_walk(&st);
	return (res);
}
