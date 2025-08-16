#include "redir.h"


/* ----- création d’un pipe heredoc et remplissage via readline ----- */
int build_heredoc_fd(t_delim d, t_shell *sh)
{
    int     hd[2];
    pid_t   pid;

    struct sigaction    sa_ignore;

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);
    sigaction(SIGQUIT, &sa_ignore, NULL);

    if (pipe(hd) < 0)
    {
        perror("pipe");
        init_signals();
        return -1;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(hd[0]);
        close(hd[1]);
        init_signals();
        return -1;
    }
    if (pid == 0)
    {
        char    *line;

        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
        rl_catch_signals = 0;
        close(hd[0]);
        while (1)
        {
            line = readline("> ");
            if (!line)
                break;
            if (ft_strcmp(line, d.clean) == 0)
            {
                free(line);
                break;
            }
            if (!d.quoted)
            {
                char *exp = expand_vars_in_line(line, sh);
                free(line);
                line = exp;
            }
            write(hd[1], line, ft_strlen(line));
            write(hd[1], "\n", 1);
            free(line);
        }
        close(hd[1]);
        _exit(0);
    }
    close(hd[1]);
    int status;
    waitpid(pid, &status, 0);
    init_signals();
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        close(hd[0]);
        return -2;
    }
    return hd[0];
}