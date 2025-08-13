#include "t_echo.h"

char *remove_quotes(const char *arg);

static int is_echo_n_flag(const char *s)
{
    if (!s || s[0] != '-')
        return 0;
    for (int i = 1; s[i]; i++)
        if (s[i] != 'n')
            return 0;
    return (s[1] != '\0'); // Au moins un 'n'
}

int builtin_echo(t_shell *shell, char **argv)
{
    {
    int i = 1;
    int newline = 1;

    // Gestion de -n répété
    while (argv[i] && is_echo_n_flag(argv[i]))
    {
        newline = 0;
        i++;
    }
    // Affichage des arguments restants
    for (; argv[i]; i++)
    {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (argv[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    (void)shell;
    return 0;
}

}

char *remove_quotes(const char *arg)
{
    size_t i = 0, j = 0;
    bool in_sq = false, in_dq = false;
    char *res = malloc(ft_strlen(arg) + 1);
    if (!res)
        return NULL;

    while (arg[i])
    {
        if (arg[i] == '\'' && !in_dq)
        {
            // Cette quote simple est un délimiteur (pas dans des doubles quotes)
            in_sq = !in_sq;
            i++; // On l'ignore (délimiteur)
        }
        else if (arg[i] == '"' && !in_sq)
        {
            // Cette quote double est un délimiteur (pas dans des simples quotes)
            in_dq = !in_dq;
            i++; // On l'ignore (délimiteur)
        }
        else
        {
            // Tout autre caractère, y compris les quotes qui ne sont PAS des délimiteurs
            res[j++] = arg[i++];
        }
    }
    res[j] = '\0';
    return res;
}
