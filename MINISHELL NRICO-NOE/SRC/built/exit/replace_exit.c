/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:28:49 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 18:47:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	ctx_init(t_stx *c)
{
	c->in_sq = false;
	c->in_dq = false;
	c->i = 0;
	c->j = 0;
}

size_t	count_exit_patterns(const char *s)
{
	t_stx	c;
	bool	handled;

	if (!s)
		return (0);
	ctx_init(&c);
	while (s[c.i])
	{
		handled = false;
		if (try_quote(s, &c, NULL))
			handled = true;
		if (!handled && try_exit(s, &c, NULL, NULL))
			handled = true;
		if (!handled)
			c.i++;
	}
	return (c.j);
}

char	*fill_with_replacement(const char *input, const char *code_str,
		size_t out_len)
{
	t_stx	c;
	t_rep	r;
	char	*res;
	bool	handled;

	ctx_init(&c);
	r.code = code_str;
	r.clen = ft_strlen(code_str);
	res = (char *)malloc(out_len + 1);
	if (!res)
		return (NULL);
	while (input[c.i])
	{
		handled = try_quote(input, &c, res);
		if (!handled)
			handled = try_exit(input, &c, res, &r);
		if (!handled)
			res[c.j++] = input[c.i++];
	}
	res[c.j] = '\0';
	return (res);
}
