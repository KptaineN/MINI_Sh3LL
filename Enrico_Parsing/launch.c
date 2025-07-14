/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/14 14:36:08 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        // Execute
        exit(1);
    }

    if (shell->fd_in != STDIN_FILENO)
            close(shell->fd_in);
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
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        // Execute
        exit(1);
    }
    close(prev_pipe[0]);
    close(prev_pipe[1]);
    if (shell->fd_out != STDOUT_FILENO)
        close(shell->fd_out);

    return pid;
}

void one_command(t_shell *shell)
{
    int pid = fork();
    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    
    if (pid == 0)
    {
    
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        // Execute command here
        // execve(...);
        exit(1);
    }
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




