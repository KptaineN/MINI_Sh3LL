/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:07 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:50:05 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	is_valid_key_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	is_echo_n_flag(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (s[1] != '\0');
}

int	builtin_echo(t_shell *shell, char **argv)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	i = 1;
	newline = 1;
	while (argv[i] && is_echo_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	(void)shell;
	return (0);
}

char	*remove_quotes(const char *arg)
{
	size_t	i;
	size_t	j;
	bool	in_sq;
	bool	in_dq;
	char	*res;

	i = 0;
	j = 0;
	in_sq = false;
	in_dq = false;
	res = malloc(ft_strlen(arg) + 1);
	if (!res)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_dq)
		{
			in_sq = !in_sq;
			i++;
		}
		else if (arg[i] == '"' && !in_sq)
		{
			in_dq = !in_dq;
			i++;
		}
		else
		{
			res[j++] = arg[i++];
		}
	}
	res[j] = '\0';
	return (res);
}
