/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:37:02 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



/* Initialise les champs de base du shell */
void init_idx(t_shell *shell)
{

    /* Descripteurs par défaut */
    shell->fd_in  = STDIN_FILENO;
    shell->fd_out = STDOUT_FILENO;

    /* Pas de heredoc pour l'instant */
    shell->heredoc = NULL;

    /* Comptages et pointeurs initiaux */
    shell->n_tokens   = 0;
    shell->n_cmd      = 0;
    shell->tokens     = NULL;
    shell->cmd_head   = NULL;
    shell->cmd_tail   = NULL;
    shell->pids       = NULL;
    shell->fd_pid[0]  = -1;
    shell->fd_pid[1]  = -1;
    shell->parsed_args= NULL;
    shell->bcmd       = NULL;
    shell->oper       = NULL;
}

static void init_pwd_home(t_shell *shell)
{
    char buf[4096];

    if (!find_env_value(shell->env, "PWD")) {
        if (getcwd(buf, sizeof(buf)))
            set_env_value(&shell->env, "PWD", buf);
    }
    if (!find_env_value(shell->env, "HOME")) {
        const char *sys_home = getenv("HOME");
        if (sys_home && *sys_home)
            set_env_value(&shell->env, "HOME", (char*)sys_home);
    }
}


/* Initialise le shell avant la boucle */
void init_shell(t_shell *shell, char **envp)
{
    if (!shell || !envp)
        return;

    shell->args        = NULL;
    shell->exit_status = 0;
    shell->input       = NULL;

    /* On passe shell, pas &shell */
    init_idx(shell);
      /* Environnement */
    shell->env = init_env(envp);
    if (!shell->env)
    {
        perror("Error initializing environment");
        exit(EXIT_FAILURE);
    }
    init_pwd_home(shell);
    init_all_t_arr(shell);
}

/* Démarrage du shell */
int start_shell(t_shell *shell, char **envp)
{
    if (!shell)
        return 0;

    ft_bzero(shell, sizeof(t_shell));
    init_signals();
    init_shell(shell, envp);

    return 1;
}
