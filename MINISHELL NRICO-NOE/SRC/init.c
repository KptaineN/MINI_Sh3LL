#include "../include/minishell.h"

void	init_minishell(t_minishell *shell, char **envp)
{
    shell->envp = envp;
    shell->env = init_env(envp); // Initialize the environment linked list
    shell->args = NULL;
    shell->input = NULL;
    shell->exit_status = 0;
    shell->ast = NULL; // Initialize the AST to NULL

    // Initialize other components as needed
    // For example, set up signal handlers, initialize data structures, etc.
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

int start_init_minishell(t_minishell *shell, char **envp)
{
    if (!shell || !envp)
        return 0;

    init_minishell(shell, envp);
    looping(shell);
    // Here, you can add any additional initialization steps needed for your minishell

    // Additional initialization steps can be added here
    // For example, setting up signal handlers, initializing the AST, etc.

    return 1; // Return 1 on success
}
