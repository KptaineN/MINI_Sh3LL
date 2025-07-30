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

#include "../../include/minishell.h"

void replace_or_add_env(t_list **env, const char *key, const char *value)
{
    t_list *current = *env;
    size_t key_len = ft_strlen(key);
    char *new_str;

    while (current)
    {
        char *entry = (char *)current->content;
        // On veut une égalité parfaite sur la clé, puis un '=' juste après
        if (ft_strncmp(entry, key, key_len) == 0 && entry[key_len] == '=')
        {
            // Trouvé : on remplace
            free(current->content);
            new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
            if (!new_str) exit(1);
            sprintf(new_str, "%s=%s", key, value);
            current->content = new_str;
            return;
        }
        current = current->next;
    }
    // Pas trouvé, ajoute à la fin
    new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
    if (!new_str) exit(1);
    sprintf(new_str, "%s=%s", key, value);
    t_list *new_node = ft_lstnew(new_str);
    ft_lstadd_back(env, new_node);
}

/*
void add_pid_env(t_shell *shell, int fd)
{
    pid_t received_pid = 0;
    char s[20]; //PID= + sizeof(pid_t) =
    if (read(fd, s, 20) > 0)
        perror("add_pid_func");   
    ft_itoa_inplace(&s[4], (int) received_pid);
    replace_or_add_env(&(shell->env), "PID=", s);
}*/
 void add_pid_env(t_shell *shell, int fd)
 {
     pid_t received_pid = 0;
     // pid_t received_pid;
     ssize_t n = 0;
     char s[20]; //PID= + sizeof(pid_t) =
     if (read(fd, s, 20) > 0)
         perror("add_pid_func");   
     ft_itoa_inplace(&s[4], (int) received_pid);
     replace_or_add_env(&(shell->env), "PID=", s);
     n = read(fd, &received_pid, sizeof(received_pid));
     if (n < 0)
     {
         perror("add_pid_env: read");
         return;
     }
     if (n == 0)
     {
         fprintf(stderr, "add_pid_env: pipe fermé prématurément\n");
         return;
     }
     /* Convertir le PID en chaîne ASCII */
     char pid_str[20];
     /* snprintf garantit la terminaison par '\0' */
     snprintf(pid_str, sizeof(pid_str), "%d", (int)received_pid);
 
     /* Clé sans '=' : replace_or_add_env fera "PID=1234" */
     replace_or_add_env(&(shell->env), "PID", pid_str);
 }

void send_pid(int fd, int pid)
{
    write(fd, "PID=", sizeof("PID="));
    write(fd, &pid, sizeof(pid));  // Send child's PID to child
}

int start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd)
{
    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;

    if (pipe(shell->fd_pid) == -1)
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
        add_pid_env(shell, shell->fd_pid[0]);
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        close(shell->fd_pid[0]);
        close(shell->fd_pid[1]);
        //execute(shell, curr_cmd->content);
        execute_cmd(shell, (t_token *)curr_cmd->content);
        exit(1);
    }

    if (shell->fd_in != STDIN_FILENO)
        close(shell->fd_in);
    send_pid(shell->fd_pid[1], pid);
    close(curr_pipe[1]);
    close(shell->fd_pid[0]);
    close(shell->fd_pid[1]);
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    curr_cmd = curr_cmd->next;

    return pid;
}

int end_cmd(t_shell *shell, int *prev_pipe, t_list *curr_cmd)
{
    (void) curr_cmd;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;

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
        add_pid_env(shell, shell->fd_pid[0]);
        close(shell->fd_pid[0]);
        close(shell->fd_pid[1]);
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);

        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        // Execute
        execute_cmd(shell, (t_token *)curr_cmd->content);
        exit(1);
    }
    send_pid(shell->fd_pid[1], pid);
    close(shell->fd_pid[0]);
    close(shell->fd_pid[1]);

    close(prev_pipe[0]);
    close(prev_pipe[1]);
    if (shell->fd_out != STDOUT_FILENO)
        close(shell->fd_out);

    return pid;
}

void one_command(t_shell *shell)
{

    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;
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

        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
       // execute_cmd(shell, shell->parser.cmd_head);
        execute_cmd(shell, (t_token *)shell->cmd_head->content);
        //execute(shell, shell->parser.cmd_head->content);
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
void    execute_cmd(t_shell *shell, t_list *curr_cmd)
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
/*void execute_cmd(t_shell *shell, t_list *curr_cmd)
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

/*
void launch_process(t_shell *shell)
{
    int i;
    int *pid;
    int prev_pipe[2] = {-1,-1};
    int curr_pipe[2];
   // int fd_pid[2];
    t_list *curr_cmd = shell->cmd_head;  // ✅
    //    t_list *curr_cmd = shell->cmd_head;

    if (shell->n_cmd <= 1)              // ✅  
    {        
        //if (shell->n_cmd == 0)
       // {
        //    fprintf(stderr, "No command to execute.\n");
        //    return;
      //  }
        shell->n_cmd = 1;    
        one_command(shell);
        return ;
    }

    pid = malloc(sizeof(int) * shell->n_cmd);  // ✅ shell->n_cmd
    if (!pid)
        return;

    i = 0;
    if (pipe(curr_pipe) < 0)
        perror("pipe");

   // pid[i++] = start_cmd(&shell->parser, prev_pipe, curr_pipe, curr_cmd);
    pid[i++] = start_cmd(shell, prev_pipe, curr_pipe, curr_cmd);
    
        i = 0;
     if (pipe(curr_pipe) < 0)
         perror("pipe");
 
     // Première commande 
     pid[i] = fork();
     if (pid[i] < 0)
         perror("fork");
     else if (pid[i] == 0)
     {
         // Fils : setup stdin/stdout et exécution 
         dup2(curr_pipe[1], STDOUT_FILENO);
         close(curr_pipe[0]);
         close(curr_pipe[1]);
         execute_cmd(shell, (t_token *)curr_cmd->content);
         exit(EXIT_FAILURE);
     }
     // Parent : on stocke et on avance 
     shell->pids[i++] = pid[i];
     close(curr_pipe[1]);
     prev_pipe[0] = curr_pipe[0];

    while (curr_cmd->next != NULL)
    {
        if (pipe(shell->fd_pid) == -1)
            perror("fd_pid");
        pid[i] = fork();
        if (pid[i] < 0)
            perror("Forks");
        if (pid[i] == 0)
        {
           // dup2(prev_pipe[0], STDIN_FILENO);
           // close(prev_pipe[0]);
           // close(prev_pipe[1]);

            //if (i == shell->parser.n_cmd - 1)
            //    dup2(shell->parser.fd_out, STDOUT_FILENO);
            //else
            //    dup2(curr_pipe[1], STDOUT_FILENO);
            
          //  close(curr_pipe[0]);
          //  close(curr_pipe[1]);
            add_pid_env(shell, shell->fd_pid[0]);
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
            close(shell->fd_pid[0]);
            close(shell->fd_pid[1]);
            dup2(curr_pipe[1], STDOUT_FILENO);
            execute_cmd(shell, (t_token *)curr_cmd->content);
           // execute_cmd(shell, curr_cmd); // ✅ passe bien t_shell *
            exit(1); // N'oublie pas de sortir dans le fils
        }
        else
        {
            send_pid(shell->fd_pid[1], (int) pid[i]);
            close(shell->fd_pid[0]);
            close(shell->fd_pid[1]);

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

     // Commandes intermédiaires 
     curr_cmd = curr_cmd->next;
     while (curr_cmd->next)
     {
         if (pipe(curr_pipe) < 0)
             perror("pipe");
 
         pid[i] = fork();
         if (pid[i] < 0)
             perror("fork");
         else if (pid[i] == 0)
         {
             dup2(prev_pipe[0], STDIN_FILENO);
             dup2(curr_pipe[1], STDOUT_FILENO);
             close(prev_pipe[0]); close(prev_pipe[1]);
             close(curr_pipe[0]); close(curr_pipe[1]);
             execute_cmd(shell, (t_token *)curr_cmd->content);
             exit(EXIT_FAILURE);
         }
         shell->pids[i++] = pid[i];
         close(prev_pipe[0]); close(prev_pipe[1]);
         prev_pipe[0] = curr_pipe[0];
         curr_cmd = curr_cmd->next;
     }
 
     // Dernière commande 
     pid[i] = fork();
     if (pid[i] < 0)
         perror("fork");
     else if (pid[i] == 0)
     {
         dup2(prev_pipe[0], STDIN_FILENO);
         close(prev_pipe[0]);
         execute_cmd(shell, (t_token *)curr_cmd->content);
         exit(EXIT_FAILURE);
     }
     shell->pids[i++] = pid[i];
 
     // On attend tout le monde 
     for (int j = 0; j < shell->n_cmd; j++)
         waitpid(shell->pids[j], NULL, 0);
     free(pid);
}*/

void launch_process(t_shell *shell)
{
    t_list  *curr_cmd = shell->cmd_head;
    int      prev_fd  = -1;
    int      pipe_fd[2];

    for (int i = 0; i < shell->n_cmd; i++)
    {
        /* Si ce n'est pas la dernière commande, on crée un pipe */
        if (i < shell->n_cmd - 1)
        {
            if (pipe(pipe_fd) < 0)
            {
                perror("pipe");
                return;
            }
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return;
        }
        else if (pid == 0)
        {
            /* ——— Le FILS ——— */
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < shell->n_cmd - 1)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            execute_cmd(shell, (t_token *)curr_cmd->content);
            exit(EXIT_FAILURE);
        }

        /* ——— Le PARENT ——— */
        shell->pids[i] = pid;
        if (i < shell->n_cmd - 1)
        {
            close(pipe_fd[1]);
            if (prev_fd != -1)
                close(prev_fd);
            prev_fd = pipe_fd[0];
        }
        curr_cmd = curr_cmd->next;
    }

    /* On attend tous les enfants */
    for (int i = 0; i < shell->n_cmd; i++)
        waitpid(shell->pids[i], NULL, 0);

    /* On met à jour $PID avec le dernier PID */
    char pid_str[20];
    snprintf(pid_str, sizeof(pid_str), "%d", (int)shell->pids[shell->n_cmd - 1]);
    replace_or_add_env(&shell->env, "PID", pid_str);

    /* Plus de free(shell->pids) ici : c'est fait dans looping() */
}








