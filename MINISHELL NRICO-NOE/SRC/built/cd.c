/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/25 16:19:16 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int builtin_cd(char **args, t_minishell *shell)
{
    (void)shell;
	if (!args[1])
		return (chdir(getenv("HOME")));

	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	// Optionnel : mettre à jour PWD dans shell->env
	return (0);
}

int execute_external(t_ast *ast, t_minishell *shell)
{
    (void)shell;
	pid_t pid = fork();
	if (pid == 0)
	{
		execvp(ast->args[0], ast->args);
		perror("execvp");
		exit(127);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (1);
}
