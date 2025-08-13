/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:45 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 16:15:57 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_echo(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->args && shell->args[1])
	{
		i = 1;
		while (shell->args[i])
		{
			printf("%s ", shell->args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("\n");
}

void	handle_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->args[0], "cd", ft_strlen("cd") + 1) == 0)
		handle_cd(shell);
	else if (ft_strncmp(shell->args[0], "exit", ft_strlen("exit") + 1) == 0)
		handle_exit(shell);
	else if (ft_strncmp(shell->args[0], "env", ft_strlen("env") + 1) == 0)
		handle_env(shell);
	else if (ft_strncmp(shell->args[0], "export", ft_strlen("export") + 1) == 0)
		handle_export(shell);
	else if (ft_strncmp(shell->args[0], "unset", ft_strlen("unset") + 1) == 0)
		handle_unset(shell);
	else if (ft_strncmp(shell->args[0], "echo", ft_strlen("echo") + 1) == 0)
		handle_echo(shell);
	else
		fprintf(stderr, "%s: command not found\n", shell->args[0]);
}
