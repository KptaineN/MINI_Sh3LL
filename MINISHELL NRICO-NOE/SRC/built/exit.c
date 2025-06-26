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

char	*replace_exit_code(const char *input, int code)
{
	char	*res = ft_strdup(input);
	char	*pos;
	char	*code_str = ft_itoa(code);

	while ((pos = ft_strnstr(res, "$?", ft_strlen(res))))
	{
		*pos = '\0';
		char *before = ft_strdup(res);
		char *after = ft_strdup(pos + 2);
		res = ft_strjoin3(before, code_str, after, 1);
		free(after);
	}
	free(code_str);
	return (res);
}

/*
char	*replace_exit_code(const char *input, int exit_code)
{
	char	*result;
	char	*code_str;
	char	*pos;

	if (!input)
		return (NULL);
	code_str = ft_itoa(exit_code);
	pos = ft_strnstr(input, "$?", ft_strlen(input));
	if (!pos)
	{
		free(code_str);
		return (ft_strdup(input));
	}

	// Allocation : ancienne taille - 2 (pour "$?") + taille de code_str + 1
	size_t new_len = ft_strlen(input) - 2 + ft_strlen(code_str) + 1;
	result = malloc(new_len);
	if (!result)
	{
		free(code_str);
		return (NULL);
	}

	// Construction du résultat
	size_t prefix_len = pos - input;
	ft_strlcpy(result, input, prefix_len + 1); // copie jusqu’à "$?"
	ft_strlcat(result, code_str, new_len);
	ft_strlcat(result, pos + 2, new_len);

	free(code_str);
	return (result);
}
char	*replace_exit_code(const char *input, int exit_code)
{
	char	*code_str = ft_itoa(exit_code);
	char	*result;
	char	*tmp;
	char	*pos;

	if (!input || !code_str)
		return (NULL);
	tmp = ft_strdup(input);
	if (!tmp)
	{
		free(code_str);
		return (NULL);
	}

	pos = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	while (pos)
	{
		*pos = '\0';
		char *joined = ft_strjoin(tmp, code_str);
		char *rest = ft_strdup(pos + 2);
		result = ft_strjoin(joined, rest);
		free(tmp);
		free(joined);
		free(rest);
		tmp = result;
		pos = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	}
	free(code_str);
	return (tmp);
}*/
