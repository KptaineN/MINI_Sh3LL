/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/29 11:06:48 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

static void	handle_single_quoted(t_stctx *state)
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

static void	handle_double_quoted(t_stctx *state)
{
	int	start;
	int	tail;

	start = state->idx + 1;
	tail = find_c_nonescaped((char *)&state->arg[start], "\"", 1);
	if (tail < 0)
		tail = state->arg_len - start;
	state->parts[state->i].type = QUOTE_DOUBLE;
	state->parts[state->i].p = ft_substr(state->arg, start, tail);
	state->parts[state->i].len = tail;
	state->idx = start + tail + 1;
	state->i++;
}

static void	handle_unquoted(t_stctx *state)
{
	int	start;
	int	tail;

	start = state->idx;
	tail = find_c_nonescaped((char *)&state->arg[start], "\"\'", 2);
	if (tail < 0)
		tail = state->arg_len - start;
	state->parts[state->i].type = QUOTE_NONE;
	state->parts[state->i].p = ft_substr(state->arg, start, tail);
	state->parts[state->i].len = tail;
	state->idx = start + tail;
	state->i++;
}

void	subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	t_stctx	state;

	if (!container || !arg || container->n_parts <= 0)
		return ;
	state.arg = arg;
	state.arg_len = ft_strlen(arg);
	state.idx = 0;
	state.i = 0;
	state.parts = container->parts;
	while (state.idx < state.arg_len && state.i < container->n_parts)
	{
		if (arg[state.idx] == '\'' && escape_check(arg, state.idx))
			handle_single_quoted(&state);
		else if (arg[state.idx] == '\"' && escape_check(arg, state.idx))
			handle_double_quoted(&state);
		else
			handle_unquoted(&state);
	}
}
