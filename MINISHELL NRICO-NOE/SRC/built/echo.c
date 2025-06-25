#include "../../include/minishell.h"


int builtin_echo(char **args)
{
    int i = 1;

    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
        i++;

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!args[1] || ft_strncmp(args[1], "-n", 2) != 0)
        printf("\n");
    return (0);
}

int builtin_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
