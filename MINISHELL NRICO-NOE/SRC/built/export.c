/* builtin_export.c */

#include "../../include/minishell.h"   // contient les définitions de t_minishell, t_env
// Récupère le nombre de variables dans la liste.
static size_t env_count(t_minishell *shell)
{
    size_t count = 0;
    t_env *env = shell->env;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}

// Remplit un tableau de chaînes "KEY=VALUE"
static char **env_to_array(t_minishell *shell)
{
    size_t n = env_count(shell);
    char **arr = malloc((n + 1) * sizeof(char*));
    if (!arr)
        return NULL;

    t_env *env_ptr = shell->env;
    size_t i = 0;
    while (env_ptr)
    {
        size_t klen = strlen(env_ptr->key);
        size_t vlen = env_ptr->value ? strlen(env_ptr->value) : 0;
        char *entry = malloc(klen + vlen + 2); // pour '=' et '\0'
        if (!entry)
        {
            for (size_t j = 0; j < i; j++)
                free(arr[j]);
            free(arr);
            return NULL;
        }
        ft_strcpy(entry, env_ptr->key);
        if (env_ptr->value)
        {
            entry[klen] = '=';
            ft_strcpy(entry + klen + 1, env_ptr->value);
        }
        else
            entry[klen] = '\0';
        arr[i++] = entry;
        env_ptr = env_ptr->next;
    }
    arr[i] = NULL;
    return arr;
}

// Compare KEY names lex ordre, ignore values
static int cmp_env(const void *a, const void *b)
{
    const char *ea = *(const char **)a;
    const char *eb = *(const char **)b;
    const char *eq_a = ft_strchr(ea, '=');
    const char *eq_b = ft_strchr(eb, '=');
    size_t na;
    if (eq_a)
        na = (size_t)(eq_a - ea);
    else
        na = strlen(ea);
    size_t nb;
    if (eq_b)
        nb = (size_t)(eq_b - eb);
    else
        nb = strlen(eb);
    size_t n;
    if (na < nb)
        n = na;
    else
        n = nb;
    int cmp = ft_strncmp(ea, eb, n);
    if (cmp != 0)
        return cmp;
    return (int)(na - nb);
}

static void print_export_arr(char **arr)
{
    size_t i = 0;
    while (arr[i])
    {
        char *eq = ft_strchr(arr[i], '=');
        if (!eq)
        {
            printf("༼⌐ ■ل͟■ ༽_/¯ %s\n", arr[i]);
        }
        else
        {
            *eq = '\0';
            printf(" (ಠ_ಠ)=ε/̵͇̿̿/’̿’̿-%s=\"%s\"\n", arr[i], eq + 1);
            *eq = '=';
        }
        i++;
    }
}

// Libère le tableau
static void free_export_arr(char **arr)
{
    size_t i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// builtin_export sans options : liste triée
int builtin_export(char **args, t_minishell *shell)
{
    (void)args;
    size_t n = 0;
    char **arr = env_to_array(shell);
    if (!arr)
    {
        shell->exit_status = 1;
        return 1;
    }
    // compte
    while (arr[n])
        n++;
    // tri
    qsort(arr, n, sizeof(char*), cmp_env);
    // affichage
    print_export_arr(arr);
    // cleanup
    free_export_arr(arr);

    shell->exit_status = 0;
    return 0;
}
