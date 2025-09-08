/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:56 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 19:24:49 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_shell_iter(t_shell *sh, char *in)
{
	if (in)
		free(in);
	if (sh->parsed_args)
	{
		free_str_array((char **)sh->parsed_args->arr);
		free(sh->parsed_args);
		sh->parsed_args = NULL;
	}
	free_cmd_list(sh);
	free_tokens(sh);
	free(sh->pids);
	sh->pids = NULL;
}

static void	child_cleanup_shell(t_shell *sh)
{
	if (!sh)
		return ;
	if (sh->exec_envp_tmp)
		free_str_array(sh->exec_envp_tmp);
	if (sh->exec_cmd_path_tmp)
		free(sh->exec_cmd_path_tmp);
	if (sh->exec_candidates_tmp)
		free_list_str(sh->exec_candidates_tmp);
	sh->exec_envp_tmp = NULL;
	sh->exec_cmd_path_tmp = NULL;
	sh->exec_candidates_tmp = NULL;
}

void	exit_child_process(t_shell *sh, int code)
{
	child_cleanup_shell(sh);
	free_minishell(sh);
	exit(code);
}
