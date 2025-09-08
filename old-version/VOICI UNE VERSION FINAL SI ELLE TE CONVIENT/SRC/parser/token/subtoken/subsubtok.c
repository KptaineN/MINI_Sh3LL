/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsubtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:29:02 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 19:29:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

void	reset_container(t_subtoken_container *c)
{
	if (!c)
		return ;
	if (c->parts)
		free(c->parts);
	c->parts = NULL;
	c->n_parts = 0;
}

void	free_parts_prefix(t_subtoken_part *parts, int n)
{
	int	k;

	if (!parts || n <= 0)
		return ;
	k = n - 1;
	while (k >= 0)
	{
		free(parts[k].p);
		k--;
	}
}

/* init du state */
int	stctx_init(t_stctx *st, t_subtoken_container *c, char *arg)
{
	if (!st || !c || !arg || c->n_parts <= 0 || !c->parts)
		return (0);
	st->arg = arg;
	st->arg_len = ft_strlen(arg);
	st->idx = 0;
	st->i = 0;
	st->parts = c->parts;
	return (1);
}

/* une étape : choisir le handler pertinent */
void	stctx_step(t_stctx *st)
{
	if (st->arg[st->idx] == '\'' && escape_check(st->arg, st->idx))
		handle_single_quoted(st);
	else if (st->arg[st->idx] == '\"' && escape_check(st->arg, st->idx))
		handle_double_quoted(st);
	else
		handle_unquoted(st);
}

/* validation + rollback propre en cas d'échec d'allocation du dernier part */
int	validate_last_or_fail(t_subtoken_container *c, t_stctx *st)
{
	int	fail_idx;

	if (st->i <= 0)
		return (0);
	if (st->parts[st->i - 1].p)
		return (1);
	fail_idx = st->i - 1;
	free_parts_prefix((t_subtoken_part *)st->parts, fail_idx + 1);
	reset_container(c);
	return (0);
}
