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
void free_env_list(t_list *env)
{
    t_list *tmp;

    while (env)
    {
        tmp = env->next;
        if (env->content)
            free(env->content);
        free(env);
        env = tmp;
    }
}

/* ========================================
 * Libère les tokens (liste chaînée t_token)
 * ======================================== */
void free_tokens(t_shell *parser)
{
    t_token *tmp;
    t_token *next;

    if (!parser || !parser->tokens)
        return;

    tmp = parser->tokens;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->value)
            free(tmp->value);

        if (tmp->cmd_args_parts)
        {
            // Libérer tous les sous-tokens
            for (int i = 0; i < tmp->cmd_args_parts->n_parts; i++)
                if (tmp->cmd_args_parts->parts[i].p)
                    free(tmp->cmd_args_parts->parts[i].p);
            free(tmp->cmd_args_parts->parts);
            free(tmp->cmd_args_parts);
        }
        free(tmp);
        tmp = next;
    }
    parser->tokens = NULL;
}

/* ========================================
 * Libère tout le parser
 * ======================================== */
void free_parser(t_shell *parser)
{
    if (!parser)
        return;

    free_tokens(parser);
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
        free_env_list(parser->env);
    parser->env = NULL;
}

/* ========================================
 * Libère toute la structure minishell
 * ======================================== */
void free_minishell(t_shell *shell)
{
    if (!shell)
        return;

    free_parser(&shell->parser);
    if (shell->args)
        free_tab(shell->args);
    shell->args = NULL;
}


// Fichier : exit_utils.c par exemple
void	exit_shell(t_shell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history(); // nettoie readline
	exit(exit_code);
}

