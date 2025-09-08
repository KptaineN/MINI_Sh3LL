/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:26:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/07 14:06:12 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	exit_sh(t_sh *sh, int exit_code)
{
	free_sh(sh);
	rl_clear_history();
	exit(exit_code);
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
/*
int	builtin_exit(void *v_sh, void **v_argv)
{
	t_sh	*sh;
	char	**argv;

	sh = (t_sh *)v_sh;
	argv = (char **)v_argv;
	long	code;

	code = 0;
	write(1, "exit\n", 5);
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			ft_putstr_fd("┐(￣ ヘ￣)┌minish: exit: numeric argument required\n",
				2);
			exit_sh(sh, 2);
		}
		if (argv[2])
		{
			ft_putstr_fd("╮(╯ _╰ )╭minish: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(argv[1]);
		exit_sh(sh, code % 256);
	}
	exit_sh(sh, 0);
	return (0);
}*/

int	builtin_exit(void *v_sh, void **v_argv)
{
	t_sh * sh = v_sh;
	(void)	v_argv;
	free_string_array((char **)v_argv);
	close((sh->pipe_to_close[0]));
	if (sh->pipe_to_close[1] != -1)
		close((sh->pipe_to_close[1]));
	exit(0);
}

