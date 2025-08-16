/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:24:17 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 16:58:59 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool escape_check(const char *str, int idx)
{
    bool toggle = true;
    while (idx > 0 && str[--idx] == '\\')
        toggle = !toggle;
    return toggle;
}

int find_c_nonescaped(const char *str, char *needle, int size_needle)
{
	int c;
	int idx = 0;

	while (str[idx])
	{
		c = 0;
		while(c<size_needle && str[idx])
		{
			if (str[idx] == needle[c] && escape_check(str,idx))
				return idx;
			c++;
		}
		idx++;
	}
	return idx;
}

