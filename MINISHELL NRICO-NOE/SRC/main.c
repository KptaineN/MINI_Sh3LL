
#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    t_minishell    shell;

    if (!init_minishell(&shell, envp))
    {
        ft_putendl_fd("Error initializing minishell\n",  STDERR_FILENO);
        exit (EXIT_FAILURE);
    }

}