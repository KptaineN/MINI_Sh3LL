/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:00:00 by nkief             #+#    #+#             */
/*   Updated: 2025/09/08 19:18:17 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_quotes(const char *s, int i, bool *in_sq, bool *in_dq)
{
	if (s[i] == '\'' && !*in_dq && escape_check(s, i))
		*in_sq = !*in_sq;
	else if (s[i] == '"' && !*in_sq && escape_check(s, i))
		*in_dq = !*in_dq;
}
