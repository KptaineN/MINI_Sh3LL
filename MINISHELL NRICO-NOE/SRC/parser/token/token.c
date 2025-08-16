/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:27 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 17:05:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


/* =============================
 * Compte le nombre de commandes
 * ============================= */
int count_tokens(t_shell *shell, t_arr *parsed_args, t_arr *oper)
{
    int count;
    int i;
    int idx_oper;
    int n_args;

    if (!parsed_args || !parsed_args->arr)
        return 0;
    count = 0;
    i = 0;
    while (i < parsed_args->len)
    {
        idx_oper = is_in_t_arr_dic_str(oper, parsed_args->arr[i]);
        if (idx_oper != -1)
        {
            count++;
            if (idx_oper < 2 || idx_oper > 4)
            {
                int consumed = file_access_redirection(shell, parsed_args->arr, idx_oper, i);
                i += consumed;
                continue;
            }
            else
                i++;
        }
        else
        {
            count++;
            n_args = count_args_cmd(shell, i);
            i += n_args;
        }
    }
    return count;
}

/* =============================
 * Attribution du type de token
 * ============================= */
void attribute_token_type(t_shell *shell)
{
    int i = 0, idx_token = 0;
    void **arr = shell->parsed_args->arr;

    if (!arr || shell->parsed_args->len <= 0)
    {
        shell->n_tokens = 0;
        return;
    }

    shell->n_tokens = count_tokens(shell, shell->parsed_args, shell->oper);
    shell->tokens = (t_token *)calloc(shell->n_tokens, sizeof(t_token));
    if (!shell->tokens)
    {
        perror("Erreur allocation tokens");
        exit(EXIT_FAILURE);
    }

    while (i < shell->parsed_args->len && idx_token < shell->n_tokens)
    {
        t_token *token = &shell->tokens[idx_token];
        //token->value = arr[i]; // If arr[i] is reused elsewhere, consider duplicating with strdup(arr[i])
        token->value = ft_strdup(arr[i]);
        if (!token->value)
        {
            perror("Erreur allocation token value");
            exit(EXIT_FAILURE);
        }
        if (is_in_t_arr_dic_str(shell->oper, arr[i]) != -1)
        {
            token->type = TOKEN_OPER;
            i++;
        }
        else
        {
            token->type = (is_in_t_arr_str(shell->bcmd, arr[i]) != -1) ? TOKEN_BCMD : TOKEN_CMD;

            int nb_args = count_args_cmd(shell, i);
            //printf("[DEBUG] attribute_token_type: token '%s' has %d args\n", token->value, nb_args);
            if (nb_args <= 0) nb_args = 1;

            int new_i = attribute_cmd_subtokens(shell, token, i, nb_args);
            //printf("[DEBUG] attribute_token_type: new_i = %d, i = %d\n", new_i, i);
            i = (new_i > i) ? new_i : i + 1;
        }
        idx_token++;
    }
}

