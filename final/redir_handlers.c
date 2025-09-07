/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:55:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 14:12:02 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int handle_heredoc(void *v_file,void **v_arr, int *fd)
{
    (void)  v_arr;
    (void) v_file;
    (void) fd;

	return 1;
}

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