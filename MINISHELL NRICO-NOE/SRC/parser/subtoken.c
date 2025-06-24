/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:54:19 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/24 14:03:00 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void attribute_subtoken_type(t_token *token)
{
	const char *subtoken;
	const char *tail;
	t_subtoken *parts;	
	int n_parts = token->u.all_parts.n_parts;
	token->u.all_parts.parts = malloc(sizeof(t_subtoken)*n_parts);
	if (!token->u.all_parts.parts)
		return;
	subtoken = token->value;
	parts = token->u.all_parts.parts;
	int i = 0;
	while(*subtoken)
	{
		if (*subtoken == '\'')
		{	
			subtoken++;
			parts[i].type = QUOTE_SINGLE;
			tail = find_c_needle(subtoken,"\'", 1);
			tail--;
		}
		else if (*subtoken == '\"')
		{	
			subtoken++;
			parts[i].type = QUOTE_DOUBLE;
			tail = find_c_needle(subtoken,"\"", 1);
			tail--;
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			tail = find_c_needle(subtoken,"\"\'",2);
		}
		parts[i].len = (int)(tail-subtoken)+1;
		parts[i].p = (char *)subtoken;
		subtoken = tail;
		if (parts[i].type != QUOTE_NONE)
			subtoken+=2;
		i++;
	}
}