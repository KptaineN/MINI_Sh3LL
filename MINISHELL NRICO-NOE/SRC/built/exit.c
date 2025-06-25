#include "../../include/minishell.h"

int	is_numeric(const char *str)
{
	int	i = 0;

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

int	builtin_exit(t_ast *node, t_minishell *shell)
{
	long	code;

	write(1, "exit\n", 5);
	if (node->args[1])
	{
		if (!is_numeric(node->args[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit_shell(shell, 255);
		}
		if (node->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(node->args[1]);
		exit_shell(shell, code % 256);
	}
	exit_shell(shell, 0);
	return (0);
}

