/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:19:25 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:22:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_exp_len(t_subtoken *b, int *k)
{
	int	var_len;

	var_len = 0;
	if (ft_isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_')
	{
		var_len = 1;
		while (*k + 1 + var_len < b->len && (ft_isalnum(b->p[*k + 1 + var_len])
				|| b->p[*k + 1 + var_len] == '_'))
			var_len++;
	}
	return (var_len);
}

int	sum_parts_len(t_subtoken_container *a)
{
	int	total;
	int	idx;

	total = 0;
	idx = 0;
	while (idx < a->n_parts)
	{
		total += a->parts[idx].len;
		idx++;
	}
	return (total);
}
