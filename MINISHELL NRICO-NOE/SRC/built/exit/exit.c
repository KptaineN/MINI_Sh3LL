/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:26:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 18:13:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

size_t	compute_out_len(size_t input_len, size_t count, size_t code_len)
{
	size_t	pattern_len;

	pattern_len = 2;
	if (count == 0)
		return (input_len);
	return (input_len + count * (code_len - pattern_len));
}

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
			ft_putstr_fd("┐(￣ ヘ￣)┌minishell: exit: numeric argument required\n",
				2);
			exit_shell(shell, 2);
		}
		if (argv[2])
		{
			ft_putstr_fd("╮(╯ _╰ )╭minishell: exit: too many arguments\n", 2);
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
	char	*code_str;
	size_t	code_len;
	size_t	count;
	size_t	out_len;
	char	*res;

	code_len = 0;
	count = 0;
	out_len = 0;
	if (!input)
		return (NULL);
	code_str = ft_itoa(code);
	if (!code_str)
		return (NULL);
	code_len = ft_strlen(code_str);
	count = count_exit_patterns(input);
	out_len = compute_out_len(ft_strlen(input), count, code_len);
	res = fill_with_replacement(input, code_str, out_len);
	free(code_str);
	return (res);
}
