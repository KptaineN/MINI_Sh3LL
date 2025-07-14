



#include "../../include/minishell.h"

static void unset_one(t_env **env, const char *key)
{
    t_env *prev = NULL, *cur = *env;
    while (cur)
    {
        if (ft_strcmp(cur->key, key) == 0)
        {
            if (prev) prev->next = cur->next;
            else      *env = cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->next;
    }
}
int builtin_unset(char **args, t_minishell *shell)
{
    // args[0] == "unset"
    int i = 1;
    while (args[i])
    {
        unset_one(&shell->env, args[i]);
        i++;
    }
    shell->exit_status = 0;
    return 0;
}


