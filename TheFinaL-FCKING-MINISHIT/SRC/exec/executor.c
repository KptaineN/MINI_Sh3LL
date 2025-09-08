/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 19:25:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_builtin_if_any(t_shell *shell, char **args)
{
	int	idx;
	int	(*handler)(t_shell *, char **);

	idx = is_in_t_arr_str(shell->bcmd, args[0]);
	if (idx == -1)
		return (0);
	handler = get_builtin_handler(shell->bcmd, idx);
	if (!handler)
	{
		free_str_array(args);
		exit_child_process(shell, 1);
	}
	shell->exit_status = handler(shell, args);
	free_str_array(args);
	exit(shell->exit_status);
	return (1);
}

void	cmd_not_found(t_shell *shell, t_token *cmd, char **args, int code)
{
	if (args)
		free_str_array(args);
	write(2, cmd->value, ft_strlen(cmd->value));
	write(2, ": command not found\n", 21);
	exit_child_process(shell, code);
}

void	prepare_or_run_builtin(t_shell *shell, t_token *cmd, char ***out_args)
{
	char	**args;
	int		(*handler)(t_shell *, char **);

	if (!cmd || !cmd->value)
		exit_child_process(shell, 1);
	args = expand_cmd(cmd, shell->env);
	if (!args || !args[0])
		cmd_not_found(shell, cmd, args, 1);
	if (is_in_t_arr_str(shell->bcmd, args[0]) != -1)
	{
		handler = get_builtin_handler(shell->bcmd, is_in_t_arr_str(shell->bcmd,
					args[0]));
		if (!handler)
		{
			free_str_array(args);
			exit_child_process(shell, 1);
		}
		shell->exit_status = handler(shell, args);
		free_str_array(args);
		exit(shell->exit_status);
	}
	*out_args = args;
}
