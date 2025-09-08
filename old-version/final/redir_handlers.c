/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:55:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 14:43:04 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 24
int handle_heredoc(void *v_file, void **v_arr, int *fd)
{
    (void) v_arr;
    char *delimiter = (char *)v_file;
    char *line;
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }
    while (1) {
        line = readline("> ");
        if (line == NULL || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        // TODO: If needed, expand variables in line using v_arr (env)
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    if (fd[0] != -1)
        close(fd[0]);
    return 0;
}
// »»-----► Number of lines: 13
int input_redirection(void *v_file,void **v_arr, int *fd)
{	
    (void)fd;
    (void)  v_arr;
    char *file = v_file;
    int fd_file = open(file, O_RDONLY);
    if (fd_file == -1) {
        perror("input redirection");
        exit(1);
    }
    dup2(fd_file, STDIN_FILENO);
    if (fd[0] != -1)
        close(fd[0]);
    close(fd_file);
    return 0;
}
// »»-----► Number of lines: 13
int output_redirection(void *v_file,void **v_arr, int *fd)
{
    (void)fd;
    (void)  v_arr;
    char *file = v_file;
    int fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_file == -1) {
        perror("output redirection");
        exit(1);
    }
    dup2(fd_file, STDOUT_FILENO);
    if (fd[1] != -1)
       close(fd[1]);
    close(fd_file);
    return 0;
}
// »»-----► Number of lines: 13
int append_redirection(void *v_file,void **v_arr, int *fd)
{
    (void)fd;
    (void)  v_arr;
    char *file = v_file;
    int fd_file = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_file == -1) {
        perror("append redirection");
        exit(1);
    }
    dup2(fd_file, STDOUT_FILENO);
    if (fd[1] != -1)
        close(fd[1]);
    close(fd_file);
    return 0;
}