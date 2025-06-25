/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:32:25 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/25 16:04:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exec_cmd_node(t_ast *ast, t_env *env, int input_fd)
{
	pid_t pid;
	char *cmd_path;
	char **env_tab;

	pid = fork();
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		setup_redirections(ast);
		cmd_path = find_cmd(ast->args[0], env);
		env_tab = env_to_envp(env);
		execve(cmd_path, ast->args, env_tab);
		perror("execve");
		exit(127);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	waitpid(pid, NULL, 0);
}

void exec_pipe_node(t_ast *ast, t_env *env, int input_fd)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_ast_pipeline(ast->left, env, input_fd);
		exit(0);
	}
	close(fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	execute_ast_pipeline(ast->right, env, fd[0]);
	waitpid(pid, NULL, 0);
}

void execute_ast_pipeline(t_ast *ast, t_env *env, int input_fd)
{
	if (ast->type == NODE_COMMAND)
		exec_cmd_node(ast, env, input_fd);
	else if (ast->type == NODE_PIPE)
		exec_pipe_node(ast, env, input_fd);
}
