/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/24 15:34:02 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int is_builtin(const char *cmd) {
    // Ex: "cd", "echo", etc. À compléter
	(void)cmd;  // silence warning if non utilisé
     // TODO : renvoyer 1 si cmd est dans la liste des builtins
     return (0);
    return 0;
}
int execute_builtin(t_ast *cmd, t_env *env) {
	//void(cmd)(t_ast *, t_env);
    // À compléter selon ta logique
	(void)cmd;  // silence warning
    (void)env;  // silence warning
     // TODO : appeler la bonne fonction builtin selon cmd->value

    return 0;
}

 /*
int	is_builtin(t_ast *ast)
{
	if (!ast || ast->type != NODE_COMMAND || !ast->args || !ast->args[0])
		return (0);
	if (ft_strcmp(ast->args[0], "cd") == 0)
		return (1);
		
	if (ft_strcmp(ast->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minishell *shell, t_ast *ast)
{
	// Ici, appelle la fonction builtin correspondante
	if (ft_strcmp(ast->args[0], "echo") == 0)
		ft_echo(ast->args); // à écrire
	else if (ft_strcmp(ast->args[0], "cd") == 0)
		ft_cd(shell, ast->args); // à écrire
	else if (ft_strcmp(ast->args[0], "exit") == 0)
		ft_exit(shell, ast->args); // à écrire
	// ... etc
}

void	execute_simple(t_ast *ast, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**env_tab;
			int fd;

	pid = fork();
	if (pid == 0)
	{
		// Ici, gère les redirections avant d’exécuter
		if (ast->filename)
		{
			if (ast->type == NODE_REDIR_OUT)
				fd = open(ast->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (ast->type == NODE_REDIR_APPEND)
				fd = open(ast->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (ast->type == NODE_REDIR_IN)
				fd = open(ast->filename, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			if (ast->type == NODE_REDIR_IN)
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
		}
		// Cherche le chemin du binaire
		cmd_path = find_cmd(ast->args[0], env);
		if (!cmd_path)
		{
			perror("command not found");
			exit(127);
		}
		env_tab = env_to_char_tab(env);
		execve(cmd_path, ast->args, env_tab);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
}
*/