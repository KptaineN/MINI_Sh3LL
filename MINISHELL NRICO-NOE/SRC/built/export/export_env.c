#include "export.h"

t_env *find_env_var(t_minishell *shell, const char *key)
{
    for (t_env *env = shell->env; env; env = env->next)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env;
    }
    return NULL;
}

int update_env_var(t_env *env, const char *value)
{
    free(env->value);
    env->value = value ? ft_strdup(value) : NULL;
    return 0;
}

int create_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *new_env = malloc(sizeof(t_env));
    if (!new_env)
        return 1;

    new_env->key = ft_strdup(key);
    new_env->value = value ? ft_strdup(value) : NULL;
    new_env->next = shell->env;
    shell->env = new_env;
    return 0;
}

int set_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *existing = find_env_var(shell, key);
    return existing
        ? update_env_var(existing, value)
        : create_env_var(shell, key, value);
}
