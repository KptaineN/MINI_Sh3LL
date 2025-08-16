

#include "redir.h"
/* ----- appliquer redirections dans l’enfant du maillon ----- */
int apply_redirs_in_child(t_cmd *c, t_shell *sh)
{
    int i;
    int fd;

    i = 0;
    while (i < c->r_count)
    {
        t_redir *r = &c->r[i];
        if (r->type == R_IN)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_RDONLY);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (r->type == R_OUT_TRUNC)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_OUT_APPEND)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_HEREDOC)
        {
            t_delim d = parse_delim(r->arg);
            int hfd = build_heredoc_fd(d, sh);
            free(d.clean);
            if (hfd == -2)
                exit(130);
            if (hfd < 0)
                return 1;
            dup2(hfd, STDIN_FILENO);
            close(hfd);
        }
        i++;
    }
    return 0;
}