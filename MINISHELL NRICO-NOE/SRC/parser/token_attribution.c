/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_attribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:54:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/24 14:03:10 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_in_t_arr(t_arr *arr, char *arg)
{
    int i = 0;
    while (i < arr->len)
    {
        if (strcmp(arr->arr[i], arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}

bool is_command(char *str)
{
    // For now, we'll assume any word that's not an operator or builtin could be a command
    // You might want to implement proper command detection (PATH lookup, etc.)
    return true; // Simplified for now
}

int count_final_tokens(t_shell *shell)
{
    int count = 0;
    int i = 0;
    char **arr = shell->parsed_args->arr;
    int len = shell->parsed_args->len;
    
    while (i < len)
    {
        // Check if current token is an operator
        if (is_in_t_arr(shell->oper, arr[i]) != -1)
        {
            count++;
            i++;
        }
        // Check if current token is a builtin or command
        else if (is_in_t_arr(shell->bcmd, arr[i]) != -1 || is_command(arr[i]))
        {
            count++; // Count the command as one token
            i++;
            // Skip all arguments that follow until we hit an operator or another command
            while (i < len && is_in_t_arr(shell->oper, arr[i]) == -1 && 
					            is_in_t_arr(shell->bcmd, arr[i]) == -1 && !is_command(arr[i]))
            {
                i++;
            }
        }
        else
        {
            // Standalone word (shouldn't happen in well-formed input, but handle it)
            count++;
            i++;
        }
    }
    return count;
}

void attribute_token_type(t_shell *shell)
{
 	int t_arr_index;
    int i = 0;
	char **arr = shell->parsed_args->arr;
	int len = shell->parsed_args->len;

	while(i < len)
	{
		//OPERATOR
		t_arr_index = is_in_t_arr(shell->oper, arr[i]);
		if (t_arr_index != -1)
		{
			// Use the corresponding type from the operator_types array
			token->type = TOKEN_OPER;
			return;
		}
		//BCMD
		t_arr_index = is_in_t_arr(shell->bcmd, arr[i]);
		if (t_arr_index != -1)
		{
			token->type = TOKEN_BCMD;
			return;
		}
		// TODO: is CMD
		
		//Word token
		token->u.all_parts.n_parts = count_subtoken(token->value);
		attribute_subtoken_type(token);
	}
}

