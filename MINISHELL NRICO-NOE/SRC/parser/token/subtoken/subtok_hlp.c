/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtok_hlp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:18:47 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/29 11:02:44 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

static void	process_char(const char *str, int i, t_qstate *stock_cut)
{
	if (str[i] == '\"' && !stock_cut->in_sq && escape_check(str, i))
	{
		stock_cut->in_nq = false;
		stock_cut->in_dq = !stock_cut->in_dq;
		if (stock_cut->in_dq)
			stock_cut->count++;
	}
	else if (str[i] == '\'' && !stock_cut->in_dq && escape_check(str, i))
	{
		stock_cut->in_nq = false;
		stock_cut->in_sq = !stock_cut->in_sq;
		if (stock_cut->in_sq)
			stock_cut->count++;
	}
	else if (!stock_cut->in_sq && !stock_cut->in_dq && !stock_cut->in_nq)
	{
		stock_cut->count++;
		stock_cut->in_nq = true;
	}
}

int	count_subtokens(const char *str)
{
	t_qstate	stock_cut;
	int			i;

	stock_cut.in_sq = false;
	stock_cut.in_dq = false;
	stock_cut.in_nq = false;
	stock_cut.count = 0;
	i = 0;
	while (str[i])
	{
		process_char(str, i, &stock_cut);
		i++;
	}
	return (stock_cut.count);
}
