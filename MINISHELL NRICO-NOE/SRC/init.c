#include "../include/minishell.h"

void	init_minishell(t_minishell *shell, char **envp)
{
    shell->args = NULL; // Initialize command arguments to NULL
    shell->input = NULL; // Initialize user input to NULL
    shell->exit_status = 0; // Initialize exit status to 0
    shell->ast = NULL; // Initialize the AST to NULL
    shell->env = NULL; // Initialize the environment linked list to NULL
    if (!shell || !envp)
        return; // Check for NULL pointers
        
    shell->env = init_env(envp); // Initialize the environment linked list dans env_list
    shell->args = NULL;
    shell->input = NULL;
    shell->exit_status = 0;
    shell->ast = NULL; // Initialize the AST to NULL

    // Initialize other components as needed
    // For example, set up signal handlers, initialize data structures, etc.
}

int looping(t_minishell *shell)
{
    while (1)
    {
        shell->input = readline("minishell$ ");
        if (!shell->input)
        {
            ft_putendl_fd("exit", STDERR_FILENO);
            break;
        }
        if (ft_strlen(shell->input) > 0)
        {
            add_history(shell->input);
            parse_input(shell);      // À écrire : transforme en AST
            execute_command(shell);  // À écrire : exécute l’AST
        }
        free(shell->input);
        shell->input = NULL;
    }
    return 0;
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