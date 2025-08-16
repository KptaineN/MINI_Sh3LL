/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 17:05:24 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


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


/* =============================
 * Gestion des sous-tokens
 * ============================= */
int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
    if (!shell || !cmd_token || !shell->parsed_args || !shell->parsed_args->arr)
        return idx + 1;

    if (len <= 0)
        return idx + 1;

    t_arr *arr_arg = shell->parsed_args;
    char **args = (char **)arr_arg->arr;
    t_subtoken_container *containers = calloc(len + 1, sizeof(t_subtoken_container));
    if (!containers)
        return idx + len;

    cmd_token->cmd_args_parts = containers;
    cmd_token->n_args = len;

    //printf("[DEBUG] attribute_cmd_subtokens: len = %d, idx = %d\n", len, idx);
    for (int k = 0; k < len && idx < arr_arg->len; )
    {
        int op_idx = is_in_t_arr_dic_str(shell->oper, args[idx]);
        if (op_idx != -1 && (op_idx < 2 || op_idx > 4))
        {
            char *op = ((t_dic *)shell->oper->arr[op_idx])->key;
            if ((int)ft_strlen(args[idx]) == (int)ft_strlen(op))
                idx++;
            idx++;
            continue;
        }
        containers[k].n_parts = count_subtokens(args[idx]);
        if (containers[k].n_parts > 0)
        {
            containers[k].parts = malloc(sizeof(t_subtoken) * containers[k].n_parts);
            subtoken_of_cmd(&containers[k], args[idx]);
        }
        idx++;
        k++;
    }

    containers[len].n_parts = 0;
    containers[len].parts = NULL;

    return idx;
}

/* =============================
 * Découpage d'un argument
 * ============================= */
void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
    if (!container || !arg || container->n_parts <= 0)
        return;

    int i = 0, idx = 0, idx_tail = 0, arg_len = ft_strlen(arg);
    t_subtoken *parts = container->parts;

    while (idx < arg_len && i < container->n_parts)
    {
        if (arg[idx] == '\'' && escape_check(arg, idx))
        {
            int start = idx + 1;
            idx_tail = find_c_nonescaped(&arg[start], "\'", 1);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_SINGLE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail + 1;
        }
        else if (arg[idx] == '"' && escape_check(arg, idx))
        {
            int start = idx + 1;
            idx_tail = find_c_nonescaped(&arg[start], "\"", 1);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_DOUBLE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail + 1;
        }
        else
        {
            int start = idx;
            idx_tail = find_c_nonescaped(&arg[start], "\"\'", 2);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_NONE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail;
        }
        i++;
    }
}