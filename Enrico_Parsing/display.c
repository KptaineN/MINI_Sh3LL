/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/20 16:17:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// display subtoken
void print_all_parts(t_shell *shell)
{
	int n = 0;
	t_subtoken_conainter *container_parts;
	t_subtoken *sub_container_parts;
	
	t_token *token;
	while(n < shell->n_tokens)
	{
		token = &shell->tokens[n];
		if (token->type != TOKEN_CMD)
		{	
			printf("%s\n", token->value);
			n++;
			continue;
		}		
		int idx_parts = 0;
		int idx_subparts;

		char *types[] ={"no quote", "single quote", "double quote"};
		while(idx_parts<token->n_parts)
		{
			container_parts = &token->cmd_args_parts[idx_parts];
			idx_subparts = 0;
			while (idx_subparts<container_parts->n_parts)
			{
				sub_container_parts = &container_parts->parts[idx_subparts];
				printf("val {%.*s} \t type {%s} \t", sub_container_parts->len,sub_container_parts->p, types[sub_container_parts->type]);
				idx_subparts++;
			}
			printf("\n");
			idx_parts++;
		}
		n++;
	}
}

// Print dictionary-like array in the form key=value
void print_dic(t_arr *dic)
{
	int		i;
	char	**pair;

	i = 0;
	while (i < dic->len)
	{
		pair = (char **)dic->arr[i];
		printf("%s\t%p\n", pair[0], (void *)pair[1]);
		i++;
	}
}

