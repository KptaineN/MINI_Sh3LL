#include "../../include/minishell.h"

void handle_cd(t_minishell *shell)
{
    // Handle the 'cd' command
    if (shell->args && shell->args[1])
    {
        if (chdir(shell->args[1]) != 0)
        {
            perror("cd");
        }
    }
    else
    {
        fprintf(stderr, "cd: missing argument\n");
    }
}

void handle_exit(t_minishell *shell)
{
    // Handle the 'exit' command
    if (shell->args && shell->args[1])
    {
        int status = atoi(shell->args[1]);
        free_minishell(shell);
        exit(status);
    }
    else
    {
        free_minishell(shell);
        exit(shell->exit_status);
    }
}

void handle_env(t_minishell *shell)
{
    // Handle the 'env' command
    if (shell->env)
    {
        print_env(shell->env); // Assuming you have a function to print the environment variables
    }
    else
    {
        fprintf(stderr, "No environment variables set.\n");
    }
}

void handle_export(t_minishell *shell)
{
    // Handle the 'export' command
    if (shell->args && shell->args[1])
    {
        // Here you would typically add the variable to the environment
        // For now, we will just print it for debugging
        printf("Exporting: %s\n", shell->args[1]);
        // add_env_variable(shell->env, shell->args[1]); // Assuming you have a function to add an env variable
    }
    else
    {
        fprintf(stderr, "export: missing argument\n");
    }
}

void handle_unset(t_minishell *shell)
{
    // Handle the 'unset' command
    if (shell->args && shell->args[1])
    {
        // Here you would typically remove the variable from the environment
        // For now, we will just print it for debugging
        printf("Unsetting: %s\n", shell->args[1]);
        // unset_env_variable(shell->env, shell->args[1]); // Assuming you have a function to unset an env variable
    }
    else
    {
        fprintf(stderr, "unset: missing argument\n");
    }
}
