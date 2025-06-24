/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:52:49 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/24 14:54:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

// display subtoken
void print_all_parts(t_shell *shell)
{
	int n = 0;
	int n_parts;
	t_subtoken *parts;
	t_token *token;
	while(1)
	{
		token = &shell->tokens[n++];
		if (token->type != TOKEN_WORD)
		{	
			if (n == shell->token_count)
				return;
			continue;
		}
		n_parts = token->u.all_parts.n_parts;
		parts = token->u.all_parts.parts;
		int idx_parts = 0;
		t_subtoken *subtoken;
		char *types[] ={"no quote", "single quote", "double quote"};
		while(idx_parts<n_parts)
		{
			subtoken = &parts[idx_parts];
			printf("val {%.*s} \t type {%s} \n", subtoken->len,subtoken->p, types[subtoken->type]);
			idx_parts++;
		}
		if (n == shell->token_count)
			return;
		printf("\n");
	}
}

size_t ft_arrlen(char **arr)
{
    size_t len;

    if (!arr)
        return (0);
    
    len = 0;
    while (arr[len])
        len++;
    
    return (len);
}

void build_t_arr(t_arr **dst, char **arr_str, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(char *) * len);
    if (!(*dst)->arr)
    {
        free(*dst);
        *dst = NULL;
        return;
    }
    
    int i = 0;
    while (i < len)
    {
        (*dst)->arr[i] = ft_strdup(arr_str[i]);
        if (!(*dst)->arr[i])
        {
            // Free all previously allocated strings
            while (i > 0)
            {
                i--;
                free((*dst)->arr[i]);
            }
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        i++;
    }
}