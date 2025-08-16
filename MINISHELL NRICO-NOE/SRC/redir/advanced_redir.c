#include "../../include/minishell.h"

/* ----- utils: strip quotes & expansion flag for heredoc delimiter ----- */
t_delim parse_delim(const char *raw)
{
    t_delim d;
    size_t i;
    size_t j;

    d.raw = (char *)raw;
    d.quoted = 0;
    if (!raw)
    {
        d.clean = NULL;
        return d;
    }
    d.clean = malloc(ft_strlen(raw) + 1);
    if (!d.clean)
        return d;
    i = 0;
    j = 0;
    while (raw[i])
    {
        if (raw[i] == '\'' || raw[i] == '"')
        {
            d.quoted = 1;
            i++;
            continue;
        }
        d.clean[j++] = raw[i++];
    }
    d.clean[j] = '\0';
    return d;
}

/* ----- expansion simple pour heredoc non quoté ----- */
char *expand_vars_in_line(const char *line, t_shell *sh)
{
    char *tmp;
    char *res;

    if (!line)
        return NULL;
    tmp = replace_exit_code(line, sh->exit_status);
    res = replace_variables(tmp, sh);
    free(tmp);
    return res;
}

/* helpers for filename expansion / ambiguity */
void ambiguous(const char *original)
{
    ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
    ft_putstr_fd((char *)original, STDERR_FILENO);
    ft_putstr_fd((char *)": ambiguous redirect\n", STDERR_FILENO);
}
int is_ambiguous(const char *fname)
{
    int i;

    if (!fname || *fname == '\0')
        return 1;
    i = 0;
    while (fname[i])
    {
        if (fname[i] == ' ')
            return 1;
        i++;
    }
    return 0;
}

char *expand_filename_if_needed(char *arg, t_shell *sh)
{
    char *tmp;
    char *res;

    tmp = replace_exit_code(arg, sh->exit_status);
    res = replace_variables(tmp, sh);
    free(tmp);
    return res;
}

int run_builtin(t_cmd *c, t_shell *sh)
{
    (void)c;
    (void)sh;
    return 0;
}

char *resolve_path(const char *cmd, t_shell *sh)
{
    (void)sh;
    return (char *)cmd;
}

/* ----- intégration enfant maillon ----- */
void child_exec_maillon(t_cmd *c, t_shell *sh, int i, int ncmd, int p[][2])
{
    if (i > 0)
        dup2(p[i - 1][0], STDIN_FILENO);
    if (i < ncmd - 1)
        dup2(p[i][1], STDOUT_FILENO);
    int k = 0;
    while (k < ncmd - 1)
    {
        close(p[k][0]);
        close(p[k][1]);
        k++;
    }
    if (apply_redirs_in_child(c, sh))
        _exit(1);
    if (c->is_builtin)
        _exit(run_builtin(c, sh));

    char **envp = list_to_envp(sh->env);
    execve(resolve_path(c->argv[0], sh), c->argv, envp);
    perror("execve");
    _exit(127);
}

