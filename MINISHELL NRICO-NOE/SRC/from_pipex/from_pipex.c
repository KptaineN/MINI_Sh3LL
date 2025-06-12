/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:32:42 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:35:06 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_pipeline(t_ast *ast)
{
	if (!ast)
		return (0);
	// Si la racine est un pipe
	if (ast->type == NODE_PIPE)
		return (1);
	// Si la racine est une redirection dont le left est un pipe
	if ((ast->type == NODE_REDIR_OUT || ast->type == NODE_REDIR_IN
			|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
		&& ast->left && ast->left->type == NODE_PIPE)
		return (1);
	return (0);
}

char	*pwd_path(char *cmd, char **envlp)
{
	char *pwd;
	char *full_path;

	pwd = get_env_path(envlp, "PWD=");
	if (!pwd)
		return (NULL);
	full_path = join_with_slash(pwd, cmd);
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
