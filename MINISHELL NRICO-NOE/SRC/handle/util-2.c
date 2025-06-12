#include "../../include/minishell.h"


void handle_echo(t_minishell *shell)
{
    // Handle the 'echo' command
    if (shell->args && shell->args[1])
    {
        for (int i = 1; shell->args[i]; i++)
        {
            printf("%s ", shell->args[i]);
        }
        printf("\n");
    }
    else
    {
        printf("\n"); // Just print a newline if no arguments
    }
}

void handle_pipes(t_minishell *shell)
{
    // Handle pipes in the command
    // This is a placeholder function; you would implement actual pipe handling here
    printf("Handling pipes...\n");
}

void handle_redirection(t_minishell *shell)
{
    // Handle redirection in the command
    // This is a placeholder function; you would implement actual redirection handling here
    printf("Handling redirection...\n");
}

void handle_builtin(t_minishell *shell)
{
    // Handle built-in commands like cd, exit, env, export, unset, echo
    if (ft_strcmp(shell->args[0], "cd") == 0)
        handle_cd(shell);
    else if (ft_strcmp(shell->args[0], "exit") == 0)
        handle_exit(shell);
    else if (ft_strcmp(shell->args[0], "env") == 0)
        handle_env(shell);
    else if (ft_strcmp(shell->args[0], "export") == 0)
        handle_export(shell);
    else if (ft_strcmp(shell->args[0], "unset") == 0)
        handle_unset(shell);
    else if (ft_strcmp(shell->args[0], "echo") == 0)
        handle_echo(shell);
    else
        fprintf(stderr, "%s: command not found\n", shell->args[0]);
}

void handle_external(t_minishell *shell)
{
    // Handle external commands (not built-in)
    // This is a placeholder function; you would implement actual command execution here
    printf("Handling external command: %s\n", shell->args[0]);
    // You would typically use execvp or similar functions to execute the command
}