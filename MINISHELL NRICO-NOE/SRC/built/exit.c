/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:26:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:26:36 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	long	code;

	code = 0;
	write(1, "exit\n", 5);
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit_shell(shell, 255);
		}
		if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(argv[1]);
		exit_shell(shell, code % 256);
	}
	exit_shell(shell, 0);
	return (0);
}

char	*replace_exit_code(const char *input, int code)
{
	bool	in_sq;
	bool	in_dq;
	size_t	i;
	size_t	j;
	size_t	count;
	char	*code_str;
	size_t	code_len;
	char	*res;

	if (!input)
		return (NULL);
	code_str = ft_itoa(code);
	if (!code_str)
		return (NULL);
	code_len = ft_strlen(code_str);
	in_sq = false;
	in_dq = false;
	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (input[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (input[i] == '$' && input[i + 1] == '?' && !in_sq)
		{
			count++;
			i++;
		}
		i++;
	}
	res = malloc(ft_strlen(input) + count * (code_len - 2) + 1);
	if (!res)
	{
		free(code_str);
		return (NULL);
	}
	in_sq = false;
	in_dq = false;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dq)
		{
			in_sq = !in_sq;
			res[j++] = input[i++];
		}
		else if (input[i] == '"' && !in_sq)
		{
			in_dq = !in_dq;
			res[j++] = input[i++];
		}
		else if (input[i] == '$' && input[i + 1] == '?' && !in_sq)
		{
			ft_memcpy(res + j, code_str, code_len);
			j += code_len;
			i += 2;
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	free(code_str);
	return (res);
}
