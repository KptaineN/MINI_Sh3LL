#include "export.h"

t_env *find_env_var(t_minishell *shell, const char *key)
{
    for (t_list *node = shell->parser.env; node; node = node->next)
    {
        t_env *env = (t_env *)node->content;
        if (ft_strcmp(env->key, key) == 0)
            return env;
    }
    return NULL;
}

int update_env_var(t_env *env, const char *value)
{
    free(env->value);
    if (value != NULL)
        env->value = ft_strdup(value);
    else
        env->value = NULL;
    return 0;
}
/*
int update_env_var(t_env *env, const char *value)
{
    free(env->value);
    if (value != NULL)
        env->value = ft_strdup(value);
    else
        env->value = NULL;
    return 0;
}*/

int create_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *new_env = malloc(sizeof(*new_env));
    if (new_env == NULL)
        return 1;

    new_env->key = ft_strdup(key);
    if (value != NULL)
        new_env->value = ft_strdup(value);
    else
        new_env->value = NULL;

    t_list *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        free(new_env->key);
        free(new_env->value);
        free(new_env);
        return 1;
    }
    new_node->content = new_env;
    new_node->next = shell->parser.env;
    shell->parser.env = new_node;
    return 0;
}

int set_env_var(t_minishell *shell, const char *key, const char *value)
{
    t_env *existing = find_env_var(shell, key);

    if (existing)
        return update_env_var(existing, value);
    else
        return create_env_var(shell, key, value);
}
