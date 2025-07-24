/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/24 20:06:38 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void add_pid_env(t_shell *shell, int fd)
{
    pid_t received_pid;
    char s[20]; //PID= + sizeof(pid_t) =
    if (read(fd, s, 4) != 4)
        perror("add_pid_func");   
    if (read(fd, &received_pid, sizeof(received_pid)) < 0)
        perror("add_pid_func");
    ft_itoa_inplace(&s[4], (int) received_pid);
    replace_or_add(&shell->env,"PID=", (const char *)s);
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

    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    
    if (pid == 0)
    {
        add_pid_env(shell,curr_pipe[0]);
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        execute(shell,curr_cmd->content);
        exit(1);
    }

    if (shell->fd_in != STDIN_FILENO)
            close(shell->fd_in);
    send_pid(curr_pipe[1],pid);
    close(curr_pipe[1]); 
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    curr_cmd = curr_cmd->next;
  
    return pid;
}

int end_cmd(t_shell *shell,int *prev_pipe, t_list *curr_cmd)
{
    (void) curr_cmd;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;

    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    if (pid == 0)
    {
        add_pid_env(shell,prev_pipe[0]);
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        // Execute
        exit(1);
    }
    close(prev_pipe[0]);
    send_pid(prev_pipe[1],pid);
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

    if (pipe(fd) == -1) {
        perror("pipe failed");
    }
    
    int pid = fork();    
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    
    if (pid == 0)
    {
        int d; //debug
        scanf("%d", &d); // debug
        
        close(fd[1]);  
        add_pid_env(shell,fd[0]);
        close(fd[0]);

        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        execute(shell, shell->cmd_head->content);
        exit(1);
    }
    else
    close(fd[0]);  // Close read end
    send_pid(fd[1],pid);
    close(fd[1]);  // Close write end
    waitpid(pid,NULL,0);
}

void launch_process(t_shell *shell)
{
    int i;
    int *pid;
    int prev_pipe[2] = {-1,-1};
    int curr_pipe[2];
    t_list *curr_cmd = shell->cmd_head;

    if (shell->n_cmd == 1)
    {    
        one_command(shell);
        return ;
    }

    pid = malloc(sizeof(int)*shell->n_cmd);    
    if (!pid)
        return;
    i = 0;
    if(pipe(curr_pipe) < 0)
        perror("pipe");
    pid[i++] = start_cmd(shell, prev_pipe,curr_pipe,curr_cmd);
    while(curr_cmd->next != NULL)
    {
        pid[i] = fork();
        if (pid[i] < 0)
            perror("Forks");
        
        if (pid[i] == 0)
        {
            add_pid_env(shell,prev_pipe[0]);
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
                    
            dup2(curr_pipe[1], STDOUT_FILENO);
            close(curr_pipe[0]);
            close(curr_pipe[1]);
            // execute
            exit(1);
        }
        else
        {
            close(prev_pipe[0]);
            send_pid(prev_pipe[1], (int) pid[i]);
            close(prev_pipe[1]);
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
            if(pipe(curr_pipe) < 0)
                perror("pipe"); //ERROR
        }
        curr_cmd = curr_cmd->next;
        i++;
    }
    pid[i++] = end_cmd(shell, prev_pipe,curr_cmd);
    while(i--)
        waitpid(pid[i], NULL, 0);
    free(pid);
}




