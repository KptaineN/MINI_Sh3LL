/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:19:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/* ========================================
 * Libère un tableau de chaînes de type char**
 * ======================================== */
void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    for (i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

/* ========================================
 * Libère un tableau dynamique t_arr
 * ======================================== */
void free_t_arr(t_arr *array)
{
    if (!array)
        return;
    if (array->arr)
    {
        for (int i = 0; i < array->len; i++)
            free(array->arr[i]);
        free(array->arr);
    }
    free(array);
}

/* ========================================
 * Libère la liste chaînée de l'environnement
 * Chaque content doit être (char *) ou une struct allouée.
 * ======================================== */
void free_list_str(t_list *lst)
{
    t_list *tmp;

    while (lst)
    {
        tmp = lst->next;
        if (lst->content)
            free(lst->content);
        free(lst);
        lst = tmp;
    }
}
void free_str_array(char **arr)
{
    if (!arr) {
        printf("[DEBUG] free_str_array: arr == NULL\n");
        return;
    }
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}


void free_cmd_list(t_shell *shell)
{
    t_list *node = shell->cmd_head;
    while (node)
    {
        t_list *next = node->next;
        free(node);
        node = next;
    }
    shell->cmd_head = NULL;
    shell->cmd_tail = NULL;
    shell->n_cmd    = 0;
}


/* ========================================
 * Libère les tokens (liste chaînée t_token)
 * ======================================== */
/* ========================================
 * Libère le tableau de tokens (tableau, pas liste)
 * ======================================== */
void free_tokens(t_shell *shell)
{
    if (!shell || !shell->tokens)
        return;

    /* 1) On supprime la structure cmd_args_parts,
     *    MAIS on NE libère PAS les .p (elles aliasent parsed_args->arr,
     *    déjà libérées par free_tab).
     */
    for (int i = 0; i < shell->n_tokens; i++)
    {
        t_token *tok = &shell->tokens[i];
        if (tok->cmd_args_parts)
        {
            free(tok->cmd_args_parts->parts);
            free(tok->cmd_args_parts);
        }
    }

    /* 2) On libère le tableau de tokens lui-même */
    free(shell->tokens);
    shell->tokens   = NULL;
    shell->n_tokens = 0;
}


/* ========================================
 * Libère tout le parser
 * ======================================== */
void free_parser(t_shell *parser)
{
    if (!parser)
        return;

    //free_tokens(parser);
    if (parser->parsed_args)
        free_t_arr(parser->parsed_args);
    parser->parsed_args = NULL;

    if (parser->bcmd)
        free_t_arr(parser->bcmd);
    parser->bcmd = NULL;

    if (parser->oper)
        free_t_arr(parser->oper);
    parser->oper = NULL;

    if (parser->env)
        free_list_str(parser->env);
    parser->env = NULL;
}

/* ========================================
 * Libère toute la structure minishell
 * ======================================== */
void free_minishell(t_shell *shell)
{
    if (!shell)
        return;

    free_parser(shell);
    if (shell->args)
        free_str_array(shell->args);
    shell->args = NULL;
}

#include <unistd.h>  // pour _exit

void child_exit(char **args,
                char *cmd_path,
                char **envp,
                t_list *candidates,
                int code)
{
    if (envp)     free_str_array(envp);
    if (args)     free_str_array(args);
    if (cmd_path) free(cmd_path);
    if (candidates) free_list_str(candidates);
    _exit(code);
}




// Fichier : exit_utils.c par exemple
void	exit_shell(t_shell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history(); // nettoie readline
	exit(exit_code);
}

