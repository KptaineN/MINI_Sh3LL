/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:28:54 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 19:42:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	try_quote(const char *s, t_stx *c, char *out)
{
	char	ch;

	ch = s[c->i];
	if (!((ch == '\'' && !c->in_dq) || (ch == '"' && !c->in_sq)))
		return (0);
	if (ch == '\'' && !c->in_dq)
		c->in_sq = !c->in_sq;
	else if (ch == '"' && !c->in_sq)
		c->in_dq = !c->in_dq;
	if (out)
	{
		out[c->j] = s[c->i];
		c->j++;
	}
	c->i++;
	return (1);
}

int	try_exit(const char *s, t_stx *c, char *out, t_rep *r)
{
	if (!(c->in_sq == false && s[c->i] == '$' && s[c->i + 1] == '?'))
		return (0);
	if (out && r)
	{
		ft_memcpy(out + c->j, r->code, r->clen);
		c->j += r->clen;
	}
	else
		c->j++;
	c->i += 2;
	return (1);
}
