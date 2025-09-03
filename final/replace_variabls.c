/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variabls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:29:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:33:10 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "minish.h"

static void	rv_reset(t_rv *st)
{
	st->i = 0;
	st->j = 0;
	st->sq = false;
	st->dq = false;
}

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

static size_t	rv_walk(t_rv *st)
{
	rv_reset(st);
	while (st->a[st->i])
	{
		toggle_quotes(st->a[st->i], &st->sq, &st->dq);
		if (st->a[st->i] == '$' && !st->sq)
			rv_handle_dollar(st);
		else
			rv_emit_char(st);
	}
	if (st->out)
		st->out[st->j] = '\0';
	return (st->j);
}

char	*replace_variables(const char *arg, t_sh *sh)
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
