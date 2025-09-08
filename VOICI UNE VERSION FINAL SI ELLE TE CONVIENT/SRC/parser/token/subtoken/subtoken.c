/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkief <nkief@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/06 20:17:37 by nkief            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

void	handle_single_quoted(t_stctx *state)
{
	int	start;
	int	tail;

	start = state->idx + 1;
	tail = find_c_nonescaped((char *)&state->arg[start], "\'", 1);
	if (tail < 0)
		tail = state->arg_len - start;
	state->parts[state->i].type = QUOTE_SINGLE;
	state->parts[state->i].p = ft_substr(state->arg, start, tail);
	state->parts[state->i].len = tail;
	state->idx = start + tail + 1;
	state->i++;
}

void	handle_double_quoted(t_stctx *state)
{
	int	start;
	int	tail;

	start = state->idx + 1;
	tail = find_c_nonescaped((char *)&state->arg[start], "\"", 1);
	if (tail < 0)
		tail = state->arg_len - start;
	state->parts[state->i].type = QUOTE_DBL;
	state->parts[state->i].p = ft_substr(state->arg, start, tail);
	state->parts[state->i].len = tail;
	state->idx = start + tail + 1;
	state->i++;
}

void	handle_unquoted(t_stctx *state)
{
	int	start;
	int	tail;

	start = state->idx;
	tail = find_c_nonescaped((char *)&state->arg[start], "\"\'", 2);
	if (tail < 0)
		tail = state->arg_len - start;
	state->parts[state->i].type = QUOTE_N;
	state->parts[state->i].p = ft_substr(state->arg, start, tail);
	state->parts[state->i].len = tail;
	state->idx = start + tail;
	state->i++;
}

int	subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	t_stctx	st;

	if (!stctx_init(&st, container, arg))
		return (-1);
	while (st.idx < st.arg_len && st.i < container->n_parts)
	{
		stctx_step(&st);
		if (!validate_last_or_fail(container, &st))
			return (-1);
	}
	if (st.i < container->n_parts)
		container->n_parts = st.i;
	return (0);
}
