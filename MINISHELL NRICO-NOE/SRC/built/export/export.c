#include "../../include/minishell.h"

/*
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
// Libère partiellement le tableau d'entrées
static void free_entries(char **arr, size_t count)
{
    size_t i = 0;
    while (i < count)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Crée une chaîne "KEY=VALUE" pour une entrée d'environnement
static char *create_env_entry(t_env *env)
{
    size_t klen = ft_strlen(env->key);
    size_t vlen = env->value ? ft_strlen(env->value) : 0;
    char *entry = malloc(klen + vlen + 2); // pour '=' et '\0'
    if (!entry)
        return NULL;
    ft_strcpy(entry, env->key);
    if (env->value)
    {
        entry[klen] = '=';
        ft_strcpy(entry + klen + 1, env->value);
    }
    else
    {
        entry[klen] = '\0';
    }
    return entry;
}

// Remplit un tableau de chaînes "KEY=VALUE"
static char **env_to_array(t_minishell *shell)
{
    size_t n = env_count(shell);
    char **arr = malloc((n + 1) * sizeof(char *));
    if (!arr)
        return NULL;
    t_env *env_ptr = shell->env;
    size_t i = 0;
    while (env_ptr)
    {
        char *entry = create_env_entry(env_ptr);
        if (!entry)
        {
            free_entries(arr, i);
            return NULL;
        }
        arr[i++] = entry;
        env_ptr = env_ptr->next;
    }
    arr[i] = NULL;
    return arr;
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
            printf(" (ಠ_ಠ)=ε/̵͇̿̿/'̿'̿-%s=\"%s\"\n", arr[i], eq + 1);
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

// Vérifie si un nom de variable est valide
static int is_valid_identifier(const char *name)
{
    int i = 0;
    if (!name || !*name)
        return 0;
    
    // Doit commencer par une lettre ou underscore
    if (!ft_isalpha(*name) && *name != '_')
        return 0;
    
    // Le reste doit être alphanumérique ou underscore
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

// Trouve une variable d'environnement
static t_env *find_env_var(t_minishell *shell, const char *key)
{
    t_env *env = shell->env;
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}
// Met à jour la valeur d'une variable d'environnement existante
static int update_env_var(t_env *env, const char *value)
{
    if (env->value)
        free(env->value);
    if (value)
        env->value = ft_strdup(value);
    else
        env->value = NULL;
    return 0;
}

// Crée une nouvelle variable d'environnement et l'ajoute à la liste du shell
static int create_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *new_env = malloc(sizeof(t_env));
    if (!new_env)
        return 1;
    
    new_env->key = ft_strdup(key);
    if (value)
        new_env->value = ft_strdup(value);
    else
        new_env->value = NULL;
    new_env->next = shell->env;
    shell->env = new_env;
    return 0;
}

// Ajoute ou modifie une variable d'environnement
static int set_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *existing = find_env_var(shell, key);
    
    if (existing)
        return update_env_var(existing, value);
    
    return create_env_var(shell, key, value);
}
// Traite un argument du format KEY=VALUE
static int handle_arg_with_assignment(char *arg, t_minishell *shell)
{
    char *eq = ft_strchr(arg, '=');
    int ret = 0;

    if (eq)
    {
        // Temporarily split la chaîne en deux
        *eq = '\0';
        if (!is_valid_identifier(arg))
        {
            printf("minishell: export: `%s': not a valid identifier\n", arg);
            ret = 1;
        }
        else
        {
            if (set_env_var(shell, arg, eq + 1) != 0)
                ret = 1;
        }
        // Rétablit le '='
        *eq = '=';
    }
    return ret;
}

// Traite un argument contenant seulement la clé (KEY)
static int handle_arg_without_assignment(char *arg, t_minishell *shell)
{
    int ret = 0;

    if (!is_valid_identifier(arg))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        ret = 1;
    }
    else
    {
        t_env *existing = find_env_var(shell, arg);
        if (!existing)
        {
            if (set_env_var(shell, arg, NULL) != 0)
                ret = 1;
        }
    }
    return ret;
}
// Traite le cas où aucun argument n'est fourni
static int export_no_arguments(t_minishell *shell)
{
    char **arr = env_to_array(shell);
    if (!arr)
    {
        shell->exit_status = 1;
        return 1;
    }
    
    ft_bubble_str_sort(arr);
    print_export_arr(arr);
    free_export_arr(arr);
    
    shell->exit_status = 0;
    return 0;
}

// Traite un seul argument de l'export
static int process_export_argument(char *arg, t_minishell *shell)
{
    if (ft_strchr(arg, '='))
        return handle_arg_with_assignment(arg, shell);
    else
        return handle_arg_without_assignment(arg, shell);
}*/

// builtin_export avec gestion des arguments, fracturé en sous-fonctions
int builtin_export(char **args, t_minishell *shell)
{
    // Si pas d'arguments, affiche toutes les variables
    if (!args[1])
        return export_no_arguments(shell);
    
    int error = 0;
    int i = 1;
    while (args[i])
    {
        error |= process_export_argument(args[i], shell);
        i++;
    }
    shell->exit_status = error;
    return error;
}
