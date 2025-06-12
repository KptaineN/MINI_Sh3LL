#include "../include/minishell.h"

void	init_minishell(t_minishell *shell, char **envp)
{
    shell->envp = envp;
    shell->args = NULL;
    shell->input = NULL;
    shell->exit_status = 0;

    // Initialize other components as needed
    // For example, set up signal handlers, initialize data structures, etc.
}

// parse la string "KEY=VALUE" en t_env
t_env *create_env(char *env_str)
{
    t_env *node = malloc(sizeof(t_env));
    char *equal = strchr(env_str, '=');
    size_t key_len = equal - env_str;
    node->key = strndup(env_str, key_len);
    node->value = strdup(equal + 1);
    node->next = NULL;
    return node;
}

// construit toute la liste à partir de envp
t_env *init_env(char **envp)
{
    t_env *head = NULL, *tmp = NULL;
    int i = 0;
    while (envp[i])
    {
        t_env *node = create_env(envp[i]);
        if (!head)
            head = node;
        else
            tmp->next = node;
        tmp = node;
        i++;
    }
    return head;
}
