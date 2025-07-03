/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/03 05:24:10 by nkiefer          ###   ########.fr       */
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

	//if (ft_strcmp(ast->args[0], "unset") == 0)
	//	return (builtin_unset(ast->args, shell));
//	if (ft_strcmp(ast->args[0], "env") == 0)
	//	return (builtin_env(shell->env));
	// Si on arrive ici, c'est que la commande n'est pas un builtin reconnu
	//ft_putstr_fd("minishell: ", STDERR_FILENO);
	//ft_putstr_fd(ast->args[0], STDERR_FILENO);
	//ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (1);
}


/*
int	is_builtin(t_ast *ast)
{
	if (!ast || ast->type != NODE_COMMAND || !ast->args || !ast->args[0])
		return (0);
	if (ft_strcmp(ast->args[0], "cd") == 0)
		return (1);
		
	if (ft_strcmp(ast->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(ast->args[0], "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minishell *shell, t_ast *ast)
{
	// Ici, appelle la fonction builtin correspondante
	if (ft_strcmp(ast->args[0], "echo") == 0)
		ft_echo(ast->args); // à écrire
	else if (ft_strcmp(ast->args[0], "cd") == 0)
		ft_cd(shell, ast->args); // à écrire
	else if (ft_strcmp(ast->args[0], "exit") == 0)
		ft_exit(shell, ast->args); // à écrire
	// ... etc
}

void	execute_simple(t_ast *ast, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**env_tab;
			int fd;

	pid = fork();
	if (pid == 0)
	{
		// Ici, gère les redirections avant d’exécuter
		if (ast->filename)
		{
			if (ast->type == NODE_REDIR_OUT)
				fd = open(ast->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (ast->type == NODE_REDIR_APPEND)
				fd = open(ast->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (ast->type == NODE_REDIR_IN)
				fd = open(ast->filename, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(1);
			}
			if (ast->type == NODE_REDIR_IN)
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
		}
		// Cherche le chemin du binaire
		cmd_path = find_cmd(ast->args[0], env);
		if (!cmd_path)
		{
			perror("command not found");
			exit(127);
		}
		env_tab = env_to_char_tab(env);
		execve(cmd_path, ast->args, env_tab);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
}
*/