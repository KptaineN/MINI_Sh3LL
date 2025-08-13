/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 15:23:38 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *read_user_input(void)
{
    char *input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
    if (!input)
        write(1, "exit\n", 5);
    return (input);
}

char *expand_status(char *input, t_shell *sh)
{
    char *res = replace_exit_code(input, sh->exit_status);
    return (res);
}

int looping(t_shell *shell)
{
    char  *input;
    char  *step1;
    char  *step2;

    while (1)
    {
		// 1) lire l’input
		input = read_user_input();
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		add_history(input);
		if (ft_strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
		// 2) expansion de $?
		step1 = expand_status(input, shell);
		if (!step1)
		{
			free(input);
			continue;
		}

		// 3) expansion des variables
		step2 = replace_variables(step1, shell);
		free(step1);
		if (!step2)
		{
			free(input);
			continue;
		}

        /* 4) Parsing */
        shell->input = step2;
        shell->parsed_args = custom_split(step2, shell);
        if (!shell->parsed_args) { free(step2); free(input); continue; }

        /* Attribution des types */
        attribute_token_type(shell);
        assign_redirs(shell);

        build_cmd_list(shell);
        if (shell->n_tokens > 0 && shell->n_cmd == 0)
        {
            shell->n_cmd = 1;
            t_list *fallback = ft_lstnew(&shell->tokens[0]);
            if (!fallback) { perror("ft_lstnew"); exit(1); }
            shell->cmd_head = fallback;
            shell->cmd_tail = fallback;
        }

        /* Allocation & exécution */
        shell->pids = malloc(sizeof(pid_t) * shell->n_cmd);
        if (!shell->pids) perror("malloc pids");
        launch_process(shell);

        /* ========== CLEANUP ========== */
        /* 1) Les chaînes de parsed_args */
        free_str_array((char **)shell->parsed_args->arr);
        free(shell->parsed_args);
        shell->parsed_args = NULL;

        /* 2) Les tokens (tableau) */
		free_cmd_list(shell);
 		free_tokens(shell);

        /* 3) La liste des commandes (noeuds t_list) */
        
        /* 4) Le tableau des pids */
        free(shell->pids);
        shell->pids = NULL;

        /* 5) Les buffers */
        free(step2);
        free(input);
    }
    return 0;
}
