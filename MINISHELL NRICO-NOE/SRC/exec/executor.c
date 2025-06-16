/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/16 16:25:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	execute_ast(t_ast *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
		execute_ast_pipeline(ast, env, STDIN_FILENO);
	else
		exec_cmd_node(ast, env, STDIN_FILENO);
}

/*
Regarder le contenu de ton AST (arbre de commandes que tu as construit en parsant l’input).

Décider : est-ce que c’est…

	Un builtin ? (commande interne du shell comme cd, echo, export…)

	Un pipeline ? (plusieurs commandes reliées par des pipes,
		ex : ls | grep .c | wc -l)

	Une commande simple ? (juste un binaire sans pipe, ex : ls -l)

Appeler la fonction adaptée pour gérer le cas :

	builtin : Exécution spéciale (souvent SANS fork)

	pipeline : Exécution pipex-style (fork + pipe entre chaque)

	simple : Juste fork + execve, redirections éventuelles
*/
void	execute_command(t_minishell *shell)
{
	if (!shell->ast)
		return ;
	if (is_builtin(shell->ast))
		execute_builtin(shell, shell->ast);
	else if (is_pipeline(shell->ast))
		execute_ast_pipeline(shell->ast, shell->env, STDIN_FILENO);
	else
		execute_simple(shell->ast, shell->env);
}
/*
chatgpt v1

#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

static void exec_simple_command(t_ast *node, t_env *env)
{
	if (!node || node->type != NODE_COMMAND || !node->args)
		exit(1);

	execve(get_command_path(node->args[0], env), node->args, env_to_envp(env));
	perror("execve");
	exit(1);
}

static void exec_redirection(t_ast *node, t_env *env)
{
	int fd;

	if (node->type == NODE_REDIR_OUT)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->type == NODE_REDIR_APPEND)
		fd = open(node->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->type == NODE_REDIR_IN)
		fd = open(node->filename, O_RDONLY);
	else
		return ;

	if (fd < 0)
	{
		perror("open");
		exit(1);
	}

	if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_APPEND)
		dup2(fd, STDOUT_FILENO);
	else if (node->type == NODE_REDIR_IN)
		dup2(fd, STDIN_FILENO);

	close(fd);
	execute_ast(node->left, env);
	exit(1);
}

static void exec_pipe(t_ast *node, t_env *env)
{
	int pipefd[2];
	pid_t pid1, pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute_ast(node->left, env);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execute_ast(node->right, env);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void execute_ast(t_ast *node, t_env *env)
{
	if (!node)
		return;
	if (node->type == NODE_COMMAND)
	{
		pid_t pid = fork();
		if (pid == 0)
			exec_simple_command(node, env);
		else
			waitpid(pid, NULL, 0);
	}
	else if (node->type == NODE_PIPE)
		exec_pipe(node, env);
	else if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT ||
		node->type == NODE_REDIR_APPEND)
	{
		pid_t pid = fork();
		if (pid == 0)
			exec_redirection(node, env);
		else
			waitpid(pid, NULL, 0);
	}
}

void execute_command(t_minishell *shell)
{
	execute_ast(shell->ast, shell->env_list);
}
*/