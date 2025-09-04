/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:36:18 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/04 14:06:55 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static int	write_dollar(char *dst, int *i)
{
	int	written;

	written = 1;
	if (dst)
		dst[0] = '$';
	(*i)++;
	return (written);
}

static int	handle_dollar(char *res, const char *arg, int *i, t_sh *sh)
{
	char	*val;
	int		nb;

	val = get_dollar_value(arg, i, sh);
	if (!val)
		return (0);
	nb = ft_strlen(val);
	if (res && nb)
		ft_memcpy(res, val, nb);
	free(val);
	return (nb);
}

int	dollar_edge_cases(char *dst, const char *arg, int *i, t_sh *sh)
{
	int		k;
	char	c;

	(void) sh;
	k = *i + 1;
	c = arg[k];
	if (c == '\0')
		return (write_dollar(dst, i));
	if (c == '?')
		return (write_and_free(dst, ft_itoa(exit_status), i, k + 1));
	if (!is_valid_key_char((unsigned char)c))
		return (write_dollar(dst, i));
	return (-1);
}

int	process_dollar(char *dst, const char *arg, int *i, t_sh *sh)
{
	int	handled;

	handled = dollar_edge_cases(dst, arg, i, sh);
	if (handled >= 0)
		return (handled);
	return (handle_dollar(dst, arg, i, sh));
}