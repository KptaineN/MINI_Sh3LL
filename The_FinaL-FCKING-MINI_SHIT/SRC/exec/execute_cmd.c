/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:28:11 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:25:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	resolve_cmd_path_or_report(t_shell *sh, t_token *cmd, char **args,
		char **out_path)
{
	char	*cmd_path;

	cmd_path = find_command_path(args[0], sh->env);
	if (!cmd_path)
	{
		cmd_not_found(sh, cmd, args, 127);
		return (false);
	}
	sh->exec_cmd_path_tmp = cmd_path;
	*out_path = cmd_path;
	return (true);
}

static char	**build_envp_or_die(t_shell *sh, char **args)
{
	char	**envp;

	envp = list_to_envp(sh->env);
	if (!envp)
	{
		perror("envp");
		free_str_array(args);
		exit_child_process(sh, 1);
	}
	sh->exec_envp_tmp = envp;
	return (envp);
}

static void	execve_or_fallback(t_shell *sh, char *cmd_path, char **args,
		char **envp)
{
	execve(cmd_path, args, envp);
	free_str_array(args);
	free(cmd_path);
	free_str_array(envp);
	sh->exec_cmd_path_tmp = NULL;
	sh->exec_envp_tmp = NULL;
	if (errno == EACCES || errno == EISDIR)
		exit_child_process(sh, 126);
	else if (errno == ENOENT)
		exit_child_process(sh, 127);
	else
	{
		perror("execve");
		exit_child_process(sh, 126);
	}
}

void	execute_cmd(t_shell *shell, t_token *cmd)
{
	char	**args;
	char	*cmd_path;
	char	**envp;

	prepare_or_run_builtin(shell, cmd, &args);
	if (!resolve_cmd_path_or_report(shell, cmd, args, &cmd_path))
		return ;
	envp = build_envp_or_die(shell, args);
	execve_or_fallback(shell, cmd_path, args, envp);
}
