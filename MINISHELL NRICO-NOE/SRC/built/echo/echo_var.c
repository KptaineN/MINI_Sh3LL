/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:36:18 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:52:27 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static int	handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
{
	char	*val;
	int		nb;

	val = get_dollar_value(arg, i, sh);
	if (!val)
	{
		return (0);
	}
	nb = ft_strlen(val);
	if (nb)
		ft_memcpy(res, val, nb);
	free(val);
	return (nb);
}

static void	toggle_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

static int	process_dollar(char *dst, const char *arg, int *i, t_shell *sh)
{
	int		k;
	char	c;
	char	*s;
	int		n;

	k = *i + 1;
	c = arg[k];
	if (c == '\0')
	{
		dst[0] = '$';
		(*i)++;
		return (1);
	}
	if (c == '?')
	{
		s = ft_itoa(sh->exit_status);
		n = ft_strlen(s);
		ft_memcpy(dst, s, n);
		free(s);
		*i = k + 1;
		return (n);
	}
	if (!is_valid_key_char((unsigned char)c))
	{
		dst[0] = '$';
		(*i)++;
		return (1);
	}
	return (handle_dollar(dst, arg, i, sh));
}

char	*replace_variables(const char *arg, t_shell *sh)
{
	int		i;
	int		j;
	bool	in_sq;
	bool	in_dq;
	char	*res;

	in_sq = false;
	in_dq = false;
	i = 0;
	j = 0;
	in_sq = false;
	in_dq = false;
	res = malloc(ft_strlen(arg) * 50 + 1);
	if (!res)
		return (NULL);
	while (arg[i])
	{
		toggle_quotes(arg[i], &in_sq, &in_dq);
		if (arg[i] == '$' && !in_sq)
			j += process_dollar(&res[j], arg, &i, sh);
		else
			res[j++] = arg[i++];
	}
	res[j] = '\0';
	return (res);
}
