#include "../../include/minishell.h"


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
        size_t klen = ft_strlen(env_ptr->key);
        size_t vlen = 0;
        if (env_ptr->value)
            vlen = ft_strlen(env_ptr->value);
        char *entry = malloc(klen + vlen + 2); // pour '=' et '\0'
        if (!entry)
        {
            size_t j = 0;
            while (j < i)
            {
                free(arr[j]);
                j++;
            }
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
    if (!name || !*name)
        return 0;
    
    // Doit commencer par une lettre ou underscore
    if (!ft_isalpha(*name) && *name != '_')
        return 0;
    
    // Le reste doit être alphanumérique ou underscore
    for (int i = 1; name[i]; i++)
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
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

// Ajoute ou modifie une variable d'environnement
static int set_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *existing = find_env_var(shell, key);
    
    if (existing)
    {
        // Modifie la valeur existante
        if (existing->value)
            free(existing->value);
        if (value)
            existing->value = ft_strdup(value);
        else
            existing->value = NULL;
        return 0;
        }
        else
        {
        // Crée une nouvelle variable
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
}

// builtin_export avec gestion des arguments
int builtin_export(char **args, t_minishell *shell)
{
    // Si pas d'arguments, affiche toutes les variables
    if (!args[1])
    {
        char **arr = env_to_array(shell);
        if (!arr)
        {
            shell->exit_status = 1;
            return 1;
        }
        
        size_t n = 0;
        while (arr[n])
            n++;
        
        ft_bubble_str_sort(arr);
        print_export_arr(arr);
        free_export_arr(arr);
        shell->exit_status = 0;
        return 0;
    }
    
    // Traite chaque argument - NE PAS AFFICHER
    int error = 0;
    int i = 1;
    while (args[i])
    {
        char *eq = ft_strchr(args[i], '=');
        
        if (eq)
        {
            // Cas KEY=VALUE
            *eq = '\0';
            if (!is_valid_identifier(args[i]))
            {
                printf("minishell: export: `%s': not a valid identifier\n", args[i]);
                *eq = '=';
                error = 1;
            }
            else
            {
                if (set_env_var(shell, args[i], eq + 1) != 0)
                    error = 1;
            }
            *eq = '=';
        }
        else
        {
            // Cas KEY seulement
            if (!is_valid_identifier(args[i]))
            {
                printf("minishell: export: `%s': not a valid identifier\n", args[i]);
                error = 1;
            }
            // Vérifie si la variable existe déjà
            t_env *existing = find_env_var(shell, args[i]);
            if (!existing)
            {
                // Crée une variable sans valeur
                if (set_env_var(shell, args[i], NULL) != 0)
                    error = 1;
            }
        }
        i++;
    }
    shell->exit_status = error;
    return error;
}