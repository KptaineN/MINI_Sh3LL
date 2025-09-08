/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/28 17:08:43 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void add_pid_env(t_shell *shell, int fd)
{
    char s[20] = {0};
    ssize_t n = read(fd, s, 4 + sizeof(pid_t));
    if (n != 4 + sizeof(pid_t))
    {
        perror("add_pid_func");
        return;  // Or handle error as needed
    }
    pid_t received_pid = *(pid_t *)(&s[4]);  // Extract binary PID
    ft_itoa_inplace(&s[4], (int)received_pid);
    replace_or_add(&shell->env, "PID=", (const char *)s);
}

void send_pid(int fd, int pid)
{
    write(fd, "PID=", 4);
    write(fd, &pid, sizeof(pid));  // Send child's PID to child
}

t_token * unwrap_token(t_shell *shell)
{
    t_cmd_red * content = shell->cmd_tail->content;
    t_arr *cmd_arr = content->cmd;
    return (t_token *)cmd_arr->arr[0];
}

t_arr * unwrap_redir(t_shell *shell)
{
    return ((t_cmd_red *)shell->cmd_head->content)->redir;
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
        dup2(prev_pipe[0], STDIN_FILENO);
        dup2(curr_pipe[1], STDOUT_FILENO);
        evaluate_redir(shell->oper, unwrap_redir(shell), prev_pipe[1], prev_pipe[0]);
        close(prev_pipe[1]);
        close(curr_pipe[0]);
        close(fd_pid[0]);
        close(fd_pid[1]);
        execute(shell,unwrap_token(shell));
    }
    send_pid(fd_pid[1],pid);
    close(fd_pid[0]);
    close(fd_pid[1]);

    close(prev_pipe[0]);
    close(prev_pipe[1]);
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    
    shell->cmd_tail = shell->cmd_tail->next;

    return pid;
}

int end_cmd(t_shell *shell,int *prev_pipe, int *curr_pipe)
{
    (void)curr_pipe;
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
        evaluate_redir(shell->oper,unwrap_redir(shell), prev_pipe[1], prev_pipe[0]);
        close(prev_pipe[1]);
        execute(shell,unwrap_token(shell));
    }
    send_pid(fd_pid[1],pid);
    close(fd_pid[0]);
    close(fd_pid[1]);
    close(prev_pipe[0]);
    close(prev_pipe[1]);

    return pid;
}

void one_command(t_shell *shell)
{ 
    //int fd_std[2];
    int fd[2];
    int fd_pid[2];

    if (pipe(fd) == -1 || pipe(fd_pid) == -1 ) {
        perror("pipe failed");
    }
    

    int pid = fork();    
    printf("\n pid %d\n", pid);
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    
    if (pid == 0)
    {
        int d; //debug
        scanf("%d", &d); // debug
    
        add_pid_env(shell,fd_pid[0]);
        close(fd_pid[1]);  
        close(fd_pid[0]);
        //dup2(fd[0], STDIN_FILENO);
        //dup2(shell->fd_out, STDOUT_FILENO);
        dup2(fd[0], STDIN_FILENO);
        evaluate_redir(shell,unwrap_redir(shell), fd[1], fd[0]);
        close(fd[1]);
        close(fd[0]);
        
        execute(shell, unwrap_token(shell));//((t_token *)((t_arr *)((t_cmd_red *)shell->cmd_head->content)->cmd)->arr[0]) );
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
    int prev_pipe[2];
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
    if(pipe(curr_pipe) < 0 && pipe(prev_pipe) < 0)
        perror("pipe");
    pid[i++] = start_cmd(shell, prev_pipe, curr_pipe);
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
            dup2(curr_pipe[1], STDOUT_FILENO);
            evaluate_redir(shell->oper, unwrap_redir(shell), prev_pipe[1], prev_pipe[0]); // ((t_cmd_red *)shell->cmd_head->content)->redir
            close(prev_pipe[1]);
            close(curr_pipe[0]);
            close(fd_pid[0]);
            close(fd_pid[1]); 
            execute(shell,NULL);
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
    pid[i++] = end_cmd(shell, prev_pipe,curr_pipe);
    while(i--)
        waitpid(pid[i], NULL, 0);
    free(pid);
}




