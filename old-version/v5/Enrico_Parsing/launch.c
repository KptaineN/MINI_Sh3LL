/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 14:57:45 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void add_pid_env(t_shell *shell, int fd)
{
    pid_t received_pid = 0;
    char s[20]; //PID= + sizeof(pid_t) =
    if (read(fd, s, 20) > 0)
        perror("add_pid_func");   
    ft_itoa_inplace(&s[4], (int) received_pid);
    replace_or_add(&shell->env,"PID=", (const char *)s);
}

void send_pid(int fd, int pid)
{
    write(fd, "PID=", sizeof("PID="));
    write(fd, &pid, sizeof(pid));  // Send child's PID to child
}


int start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe)
{

    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;
    int fd_pid[2];
    if (pipe(fd_pid) == -1)
        perror("fd_pid");
    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    
    if (pid == 0)
    {
        add_pid_env(shell,fd_pid[0]);
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        close(fd_pid[0]);
        close(fd_pid[1]);
        execute(shell,shell->cmd_tail->content);
        exit(1);
    }

    if (shell->fd_in != STDIN_FILENO)
            close(shell->fd_in);
    send_pid(fd_pid[1],pid);
    close(curr_pipe[1]);
    close(fd_pid[0]);
    close(fd_pid[1]);
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    shell->cmd_tail = shell->cmd_tail->next;
    return pid;
}

int end_cmd(t_shell *shell,int *prev_pipe)
{
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;
    int fd_pid[2];
    if (pipe(fd_pid) == -1)
        perror("fd_pid");

    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    if (pid == 0)
    {
        add_pid_env(shell,fd_pid[0]);
        close(fd_pid[0]);
        close(fd_pid[1]);
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        execute(shell,shell->cmd_tail->content);
    }
    send_pid(fd_pid[1],pid);
    close(fd_pid[0]);
    close(fd_pid[1]);
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
    {
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
        execute(shell, shell->cmd_head->content);
        exit(1);
    }
    else
    close(fd[0]);  // Close read end
    close(fd_pid[0]);
    send_pid(fd_pid[1], pid);
    close(fd[1]);  // Close write end
    close(fd_pid[1]);

    waitpid(pid,NULL,0);
}

void launch_process(t_shell *shell)
{
    int *t_pid;
    int i;
    int *pid;
    int prev_pipe[2] = {-1,-1};
    int curr_pipe[2];
    int fd_pid[2];

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
    pid[i++] = start_cmd(shell, prev_pipe,curr_pipe);
    while(shell->cmd_tail->next != NULL)
    {
        if (pipe(fd_pid) == -1)
            perror("fd_pid");
        t_pid = &pid[i];
        (void) t_pid;
        pid[i] = fork();
        if (pid[i] < 0)
            perror("Forks");
        if (pid[i] == 0)
        {
            add_pid_env(shell,fd_pid[0]);
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
            close(fd_pid[0]);
            close(fd_pid[1]);
            dup2(curr_pipe[1], STDOUT_FILENO);
            close(curr_pipe[0]);
            close(curr_pipe[1]);
            execute(shell,shell->cmd_tail->content);
        }
        else
        {
            send_pid(fd_pid[1], (int) pid[i]);
            close(fd_pid[0]);
            close(fd_pid[1]);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
            if(pipe(curr_pipe) == -1)
                perror("pipe"); //ERROR
        }
        shell->cmd_tail = shell->cmd_tail->next;
        i++;
    }
    pid[i++] = end_cmd(shell, prev_pipe);
    while(i--)
        waitpid(pid[i], NULL, 0);
    free(pid);
}




