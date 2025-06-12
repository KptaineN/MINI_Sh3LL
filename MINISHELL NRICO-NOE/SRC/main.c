
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_minishell    shell;

    if (!start_init_minishell(&shell, envp))
    {
        ft_putendl_fd("Error initializing minishell\n",  STDERR_FILENO);
        exit (EXIT_FAILURE);
    }
    free_minishell(&shell);
    return (shell.exit_status);
}