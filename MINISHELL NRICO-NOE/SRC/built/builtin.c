/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/04 03:17:18 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/* Fait défiler un 🦆 de la colonne la plus à droite jusqu'à la 0,
   puis efface la ligne pour retrouver l'invite proprement. */
static void single_quack(void)
{
	struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return;
    int cols = ws.ws_col;

    const char *frames[] = { "𓆝", "𓆟", "𓆞" };
    const int nframes = 3;
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 30000000L };  /* 50 ms */

    /* Cache le curseur & sauve la position juste après le prompt */
    printf("\033[?25l\033[s");
    fflush(stdout);

    int prev_x = -1;
    for (int t = 0; ; ++t)
    {
        int x = cols - 1 - t;
        if (x < 0)
            break;
        int f = t % nframes;

        /* Efface l’ancienne position */
        if (prev_x >= 0) {
            printf("\033[u\033[%dC ", prev_x);
            fflush(stdout);
        }
        /* Affiche la nouvelle frame */
        printf("\033[u\033[%dC%s", x, frames[f]);
        fflush(stdout);

        nanosleep(&ts, NULL);
        prev_x = x;
    }

    /* Efface la dernière trace */
    if (prev_x >= 0) {
        printf("\033[u\033[%dC ", prev_x);
        fflush(stdout);
    }

    /* Restaure curseur et prompt */
    printf("\033[u\033[?25h");
    fflush(stdout);

    /* Clear entire screen and move cursor to top-left */
    printf("\033[2J\033[H");
    fflush(stdout);
}



/* builtin_quack simplifié pour un seul passage */
int builtin_quack(char **args)
{
    (void)args;       /* on n'utilise pas args ici */
    single_quack();
    return 0;
}




/*int is_builtin(const char *cmd) {
    // Ex: "cd", "echo", etc. À compléter
	(void)cmd;  // silence warning if non utilisé
     // TODO : renvoyer 1 si cmd est dans la liste des builtins
    return (0);
    return 0;
}*/
int is_builtin(t_ast *ast)
{
	if (!ast || !ast->args || !ast->args[0])
		return (0);
	return ((ft_strcmp(ast->args[0], "cd") == 0)
		|| (ft_strcmp(ast->args[0], "echo") == 0)
		|| (ft_strcmp(ast->args[0], "pwd") == 0)
		|| (ft_strcmp(ast->args[0], "export") == 0)
		|| (ft_strcmp(ast->args[0], "unset") == 0)
		|| (ft_strcmp(ast->args[0], "env") == 0)
		|| (ft_strcmp(ast->args[0], "exit") == 0))
		|| (ft_strcmp(ast->args[0], "duck") == 0)
		|| (ft_strcmp(ast->args[0], "Quack!") == 0);
}

int execute_builtin(t_ast *ast, t_minishell *shell)
{
	if (ft_strcmp(ast->args[0], "cd") == 0)
		return (builtin_cd(ast->args, shell));
	if (ft_strcmp(ast->args[0], "echo") == 0)
		return (builtin_echo(ast->args, shell));
	if (ft_strcmp(ast->args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(ast->args[0], "exit") == 0)
		return (builtin_exit(ast, shell));
	if (ft_strcmp(ast->args[0], "export") == 0)
		return (builtin_export(ast->args, shell));
	if (ft_strcmp(ast->args[0], "duck") == 0)
	{
		ft_putstr_fd("Quack! 🦆\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strcmp(ast->args[0], "Quack!") == 0)
		return (builtin_quack(ast->args));

	if (ft_strcmp(ast->args[0], "unset") == 0)
		return (builtin_unset(ast->args, shell));
	if (ft_strcmp(ast->args[0], "env") == 0)
		return (builtin_env(shell->args, shell));
	// Si on arrive ici, c'est que la commande n'est pas un builtin reconnu
	//ft_putstr_fd("minishell: ", STDERR_FILENO);
	//ft_putstr_fd(ast->args[0], STDERR_FILENO);
	//ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (1);
}

