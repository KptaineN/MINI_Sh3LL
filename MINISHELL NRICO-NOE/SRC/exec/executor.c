/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/17 15:03:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/minishell.h"


char *find_cmd(const char *cmd, t_env *env) {
    (void)cmd; (void)env;
    return NULL;
}



/*
 * Executes a simple command node (without redirections or pipes).
 */
static void exec_simple_command(t_ast *node, t_env *env)
{
	char *cmd_path;

	if (!node || node->type != NODE_COMMAND || !node->args)
		exit(1);
	cmd_path = find_command_path(node->args[0], env);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", node->args[0]);
		exit(1);
	}
	execve(cmd_path, node->args, env_to_envp(env)); // utilise la bonne fonction ici
	perror("execve");
	exit(1);
}

/*
 * Executes a redirection node.
 * Opens the file according to redirection type and duplicates the file descriptor.
 */
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
		return;
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

/*
 * Executes a pipeline node.
 * It forks two processes; the first writes to the pipe, the second reads from it.
 */
static void exec_pipe(t_ast *node, t_env *env)
{
	int     pipefd[2];
	pid_t   pid1, pid2;

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute_ast(node->left, env);
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit(1);
	}
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

/*
 * Recursively executes an AST node.
 * This function handles command nodes, pipelines, and redirections.
 */
void execute_ast(t_ast *node, t_env *env)
{
	pid_t pid;

	if (!node)
		return;
	if (node->type == NODE_COMMAND)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
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
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			exec_redirection(node, env);
		else
			waitpid(pid, NULL, 0);
	}
}

/*
 * The main entry point for executing a command.
 * If the AST represents a builtin, we execute it directly;
 * otherwise, we recursively execute the AST.
 */
void execute_command(t_minishell *shell)
{
	if (!shell->ast)
		return;
	//if (is_builtin(shell->ast))//avant test
	if (is_builtin(shell->ast->args[0]))
		execute_builtin(shell->ast, shell->env);
		//execute_builtin(shell, shell->ast);
	else
		execute_ast(shell->ast, shell->env);
}
