/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:24:17 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 15:04:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/parsking.h"
#include "../../include/minishell.h"


/*
	trouve la premiere occurence de charactere
	str = Enrico et Noe sont beau
	needle = "o" (size 1)				return: "o et Noe sont beau"
	needle = "Nc" (size 2)				return: "co et Noe sont Beau"
	du coup c'est un strchr mais que si tu voulais chercher "N" et "c" 
	et voulais prendre le premier d'entre eux, ici elle te retourne naturellement le premier
	
	UTILISÉ dans 'token_attribute_parts_type' pour quand de UNQUOTED on passe a SINGLE/DOUBLE QUOTED mais on sais pas le quel
*/
int find_c_nonescaped(const char *str, char *needle, int size_needle)
{
	int c;
	int idx = 0;

	while (str[idx])
	{
		c = 0;
		while(c<size_needle && str[idx])
		{
			if (str[idx] == needle[c] && escape_check(str,idx))
				return idx;
			c++;
		}
		idx++;
	}
	return idx;
}

/*
	Ici on token les subtokens
*/
int count_subtokens(const char *str)
{
	bool in_single_quote;
	bool in_double_quote;
	bool in_no_quote;
	int i = 0;
	int count = 0;

	in_single_quote = 0;
	in_double_quote = 0;
	in_no_quote = 0;
	while(str[i])
	{
		if (str[i] == '\"' && !in_single_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_double_quote =!in_double_quote;
			if (in_double_quote)
				count++;
		}
		else if (str[i] == '\'' && !in_double_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_single_quote =!in_single_quote;
			if (in_single_quote)
				count++;
		}
		else if (!in_single_quote && !in_double_quote && !in_no_quote)
		{	
			count++;
			in_no_quote = true;
		}
		i++;
	}
	return count;
}
/*
int count_tokens(t_shell *shell)
{
    int count = 0;
    int i = 0;
    void **arr = shell->parsed_args->arr;
    int len = shell->parsed_args->len;
    
    while (i < len)
    {
        // Check if current token is an operator
        if (is_in_t_arr_dic_str(shell->oper, arr[i]) != -1)
        {
            count++;
            i++;
        }
        // Check if current token is a builtin or command
        else if (is_in_t_arr_dic_str(shell->bcmd, arr[i]) != -1 || is_command(arr[i],shell->env))
        {
            count++; // Count the command as one token
            i++;
            // Skip all arguments that follow until we hit an operator or another command
            while (i < len && is_in_t_arr_dic_str(shell->oper, arr[i]) == -1 && 
                   is_in_t_arr_dic_str(shell->bcmd, arr[i]) == -1 && !is_command(arr[i], shell->env))
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
}*/

int count_tokens(t_shell *shell, t_arr *parsed_args, t_arr *oper)
{
    int count = 1;
    int i = 0;
    void **arr = parsed_args->arr;
    int len = parsed_args->len;
    int idx_oper;
	if (len == 0)
		return 0;
	while(i<len)
	{
		while (i<len)
		{	
			idx_oper = is_in_t_arr_dic_str(oper, arr[i]);
			if (idx_oper != -1)
			{
				if (idx_oper < 2 || idx_oper > 4)
				{
					file_access_redirection(shell, parsed_args->arr, idx_oper, i);
					ft_free((void**)&parsed_args->arr[i++]);
					if (i != len)
						ft_free((void**)&parsed_args->arr[i]);
				}
				else				
				{
					count++;
					i++;
					break;
				}
			}
			i++;
		}
	}
    return count+(idx_oper == -1);
}
