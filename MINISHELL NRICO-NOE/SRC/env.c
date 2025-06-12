#include "../include/minishell.h"

void free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}

// parse la string "KEY=VALUE" en t_env
t_env *create_env(char *env_str)
{
    t_env *node;
    char *equal;
    size_t key_len;
    
    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    equal = ft_strchr(env_str, '=');
    if (!equal)
    {   free(node);
        return NULL;
    }
    key_len = equal - env_str;
    node->key = ft_strndup(env_str, key_len);
    node->value = ft_strdup(equal + 1);
    node->next = NULL;
    return node;
}

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}