// SRC/exec/redirs_parent.c
#include "../include/minishell.h"
#include <unistd.h>
#include <stdio.h>

int apply_parent_redirs(t_shell *sh, t_fd_sav *sav)
{
    sav->saved_stdin  = dup(STDIN_FILENO);
    sav->saved_stdout = dup(STDOUT_FILENO);
    sav->closed_in = 0; sav->closed_out = 0;
    if (sav->saved_stdin < 0 || sav->saved_stdout < 0) { perror("dup"); return 1; }

    if (sh->fd_in != -1 && sh->fd_in != STDIN_FILENO) {
        if (dup2(sh->fd_in, STDIN_FILENO) < 0) { perror("dup2 fd_in"); return 1; }
        sav->closed_in = 1;
    }
    if (sh->fd_out != -1 && sh->fd_out != STDOUT_FILENO) {
        if (dup2(sh->fd_out, STDOUT_FILENO) < 0) { perror("dup2 fd_out"); return 1; }
        sav->closed_out = 1;
    }
    return 0;
}

void restore_parent_redirs(t_shell *sh, t_fd_sav *sav)
{
    (void)sh;
    if (dup2(sav->saved_stdin, STDIN_FILENO)  < 0) perror("restore stdin");
    if (dup2(sav->saved_stdout, STDOUT_FILENO) < 0) perror("restore stdout");
    close(sav->saved_stdin);
    close(sav->saved_stdout);
    if (sav->closed_in  && sh->fd_in  != -1 && sh->fd_in  != STDIN_FILENO)  close(sh->fd_in);
    if (sav->closed_out && sh->fd_out != -1 && sh->fd_out != STDOUT_FILENO) close(sh->fd_out);
}
