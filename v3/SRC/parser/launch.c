/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:57:55 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsking.h"
#include "../../include/minishell.h"

void execute_cmd(t_minishell *shell, t_list *curr_cmd);

void add_pid_env(t_minishell *shell, int fd)
{
    pid_t received_pid = 0;
    char s[20]; //PID= + sizeof(pid_t) =
    if (read(fd, s, 20) > 0)
        perror("add_pid_func");   
    ft_itoa_inplace(&s[4], (int) received_pid);
    replace_or_add(&shell->parser.env, "PID=", (const char *)s);
}

void send_pid(int fd, int pid)
{
    write(fd, "PID=", sizeof("PID="));
    write(fd, &pid, sizeof(pid));  // Send child's PID to child
}

int start_cmd(t_minishell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd)
{
    if (shell->parser.fd_in == -1)
        shell->parser.fd_in = STDIN_FILENO;

    if (pipe(shell->parser.fd_pid) == -1)
        perror("fd_pid");
    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    
    if (pid == 0)
    {
        /*dup2(shell->parser.fd_in, STDIN_FILENO);
        close(shell->parser.fd_in);
        
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);

        execute_cmd(shell, curr_cmd);
        exit(0);*/
        add_pid_env(shell, shell->parser.fd_pid[0]);
        dup2(shell->parser.fd_in, STDIN_FILENO);
        close(shell->parser.fd_in);
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        close(shell->parser.fd_pid[0]);
        close(shell->parser.fd_pid[1]);
        execute(shell, curr_cmd->content);
        exit(1);
    }

    if (shell->parser.fd_in != STDIN_FILENO)
        close(shell->parser.fd_in);
    send_pid(shell->parser.fd_pid[1], pid);
    close(curr_pipe[1]);
    close(shell->parser.fd_pid[0]);
    close(shell->parser.fd_pid[1]);
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    curr_cmd = curr_cmd->next;

    return pid;
}

int end_cmd(t_minishell *shell, int *prev_pipe, t_list *curr_cmd)
{
    (void) curr_cmd;
    if (shell->parser.fd_out == -1)
        shell->parser.fd_out = STDOUT_FILENO;

    int pid = fork();
    if (pid < 0)
        perror("Forks");

    if (pid == 0)
    /*{
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);

        dup2(shell->parser.fd_out, STDOUT_FILENO);
        close(shell->parser.fd_out);

        // Execute the command
        execute_cmd(shell, curr_cmd);
        exit(0);
    }*/
   {
        add_pid_env(shell, shell->parser.fd_pid[0]);
        close(shell->parser.fd_pid[0]);
        close(shell->parser.fd_pid[1]);
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);

        dup2(shell->parser.fd_out, STDOUT_FILENO);
        close(shell->parser.fd_out);
        // Execute
        exit(1);
    }
    send_pid(shell->parser.fd_pid[1], pid);
    close(shell->parser.fd_pid[0]);
    close(shell->parser.fd_pid[1]);

    close(prev_pipe[0]);
    close(prev_pipe[1]);
    if (shell->parser.fd_out != STDOUT_FILENO)
        close(shell->parser.fd_out);

    return pid;
}

void one_command(t_minishell *shell)
{

    if (shell->parser.fd_in == -1)
        shell->parser.fd_in = STDIN_FILENO;
    if (shell->parser.fd_out == -1)
        shell->parser.fd_out = STDOUT_FILENO;
    int fd[2];
    int fd_pid[2];

    if (pipe(fd) == -1 || pipe(fd_pid) == -1) {
        perror("pipe failed");
    }
    

    int pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {/*
        // Redirections
        if (shell->parser.fd_in != STDIN_FILENO)
        {
            dup2(shell->parser.fd_in, STDIN_FILENO);
            close(shell->parser.fd_in);
        }

        if (shell->parser.fd_out != STDOUT_FILENO)
        {
            dup2(shell->parser.fd_out, STDOUT_FILENO);
            close(shell->parser.fd_out);
        }

        // Exécute la commande (1 seule dans cmd_head)
        execute_cmd(shell, shell->parser.cmd_head);
        exit(0); // On quitte le process enfant
    }*/
        int d; //debug
        scanf("%d", &d); // debug
        
        close(fd[1]);
        close(fd_pid[0]);  
        add_pid_env(shell,fd_pid[0]);
        close(fd[0]);
        close(fd_pid[0]);

        dup2(shell->parser.fd_in, STDIN_FILENO);
        close(shell->parser.fd_in);
        dup2(shell->parser.fd_out, STDOUT_FILENO);
        close(shell->parser.fd_out);
        execute(shell, shell->parser.cmd_head->content);
        exit(1);
    }
    else
    close(fd[0]);  // Close read end
    close(fd_pid[0]);
    send_pid(fd_pid[1], pid);
    close(fd[1]);  // Close write end
    close(fd_pid[1]);

    waitpid(pid, NULL, 0); // On attend le process
}

/*
void    execute_cmd(t_minishell *shell, t_list *curr_cmd)
{
    t_token *token = curr_cmd->content;

    if (token->u.cmd_args_parts == NULL)
    {
        fprintf(stderr, "Error: No command arguments found.\n");
        return;
    }

    char **args = reconstruct_args(token->u.cmd_args_parts);
    if (args == NULL)
    {
        fprintf(stderr, "Error: Failed to reconstruct command arguments.\n");
        return;
    }

    // Check if the command is a built-in or external command
    t_subtoken first = token->u.cmd_args_parts[0].parts[0];
    
    char *cmd = ft_substr(first.p, 0, first.len);

    if (is_builtin(cmd))
    {
        free(cmd);
        execute_builtin(shell, token->idx);
        return;
    }
    free(cmd);

    if (is_command(args[0], shell->parser.env))
    {
        // Execute external command
        char *cmd_path = find_command_path(args[0], shell->parser.env);
        if (cmd_path)
        {
            execve(cmd_path, args, linked_to_array_string(shell->parser.env));
            perror("execve");
            free(cmd_path);
        }
        else
        {
            fprintf(stderr, "Command not found: %s\n", args[0]);
        }
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", args[0]);
    }
    
    // Free the args array
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}*/
/*void execute_cmd(t_minishell *shell, t_list *curr_cmd)
{
	t_token *token = curr_cmd->content;

	if (!token || !token->u.cmd_args_parts)
	{
		fprintf(stderr, "[ERROR] No command arguments found.\n");
		return;
	}

	char **args = reconstruct_args(token->u.cmd_args_parts);
	if (!args || !args[0])
	{
		fprintf(stderr, "[ERROR] Failed to reconstruct command arguments or args[0] is NULL.\n");
		free_tab(args);
		return;
	}

	// DEBUG affichage des arguments
	for (int i = 0; args[i]; i++)
		printf("[DEBUG] arg[%d] = '%s'\n", i, args[i]);

	// Récupère le nom de commande brut depuis le premier subtoken
	t_subtoken first = token->u.cmd_args_parts[0].parts[0];
	char *cmd = ft_substr(first.p, 0, first.len);
	if (!cmd)
	{
		fprintf(stderr, "[ERROR] cmd is NULL (ft_substr failed)\n");
		free_tab(args);
		return;
	}

	// Si c’est un builtin
	if (is_builtin(cmd))
	{
		free(cmd);
		execute_builtin(shell, token->idx);
		free_tab(args);
		return;
	}
	free(cmd);

	// Sinon commande externe
	if (is_command(args[0], shell->parser.env))
	{
		char *cmd_path = find_command_path(args[0], shell->parser.env);
		if (cmd_path)
		{
			execve(cmd_path, args, linked_to_array_string(shell->parser.env));
			perror("execve");
			free(cmd_path);
		}
		else
			fprintf(stderr, "Command not found: %s\n", args[0]);
	}
	else
		fprintf(stderr, "Command not found: %s\n", args[0]);

	free_tab(args);
}*/


void launch_process(t_minishell *shell)
{
    int i;
    int *pid;
    int prev_pipe[2] = {-1,-1};
    int curr_pipe[2];
   // int fd_pid[2];
    t_list *curr_cmd = shell->parser.cmd_head;  // ✅
    //    t_list *curr_cmd = shell->cmd_head;

    if (shell->parser.n_cmd == 1)                // ✅
    {    
        one_command(shell);
        return ;
    }

    pid = malloc(sizeof(int) * shell->parser.n_cmd);  // ✅ shell->n_cmd
    if (!pid)
        return;

    i = 0;
    if (pipe(curr_pipe) < 0)
        perror("pipe");

   // pid[i++] = start_cmd(&shell->parser, prev_pipe, curr_pipe, curr_cmd);
    pid[i++] = start_cmd(shell, prev_pipe, curr_pipe, curr_cmd);
    while (curr_cmd->next != NULL)
    {
        if (pipe(shell->parser.fd_pid) == -1)
            perror("fd_pid");
        pid[i] = fork();
        if (pid[i] < 0)
            perror("Forks");
        if (pid[i] == 0)
        {
           /* dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);

            if (i == shell->parser.n_cmd - 1)
                dup2(shell->parser.fd_out, STDOUT_FILENO);
            else
                dup2(curr_pipe[1], STDOUT_FILENO);
            
            close(curr_pipe[0]);
            close(curr_pipe[1]);*/
            add_pid_env(shell, shell->parser.fd_pid[0]);
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
            close(shell->parser.fd_pid[0]);
            close(shell->parser.fd_pid[1]);
            dup2(curr_pipe[1], STDOUT_FILENO);

            execute_cmd(shell, curr_cmd); // ✅ passe bien t_minishell *
            exit(1); // N'oublie pas de sortir dans le fils
        }
        else
        {
            send_pid(shell->parser.fd_pid[1], (int) pid[i]);
            close(shell->parser.fd_pid[0]);
            close(shell->parser.fd_pid[1]);

            close(prev_pipe[0]);
            close(prev_pipe[1]);
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
            if (pipe(curr_pipe) < 0)
                perror("pipe");
        }
        curr_cmd = curr_cmd->next;
        i++;
    }
    pid[i++] = end_cmd(shell, prev_pipe, curr_cmd);
    //pid[i++] = end_cmd(&shell->parser, prev_pipe, curr_cmd);
    while (i--)
        waitpid(pid[i], NULL, 0);
    free(pid);
}








