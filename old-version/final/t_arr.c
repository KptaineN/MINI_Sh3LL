/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:52:35 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:34:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 14
int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    int i = 0;
    t_dic *dic;
    
    if (!arr || !arg)
        return (-1);
    
    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        if (dic && dic->key && ft_strcmp((char *)dic->key, arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}
// »»-----► Number of lines: 24
static void build_t_arr_dic_str(t_arr **dst, char **keys, void **values, int len)
{
    *dst = malloc(sizeof(t_arr));
    t_dic *temp;
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);   // OK: array of pointers
    if (!(*dst)->arr)
        return;

    temp = malloc(sizeof(t_dic) * len);            // FIXED: struct-sized blocks
    if (!temp)
        return;
    
    int i = 0;
    while (i < len)
    {
        temp[i].key   = ft_strdup(keys[i]);         // duplicate key
        temp[i].value = values[i];                  // store handler ptr
        (*dst)->arr[i] = &temp[i];                  // point into temp[]
        if (!temp[i].key)
            return;
        //printf("%s\t%p\n", (char *)temp[i].key, (int*)temp[i].value);
        i++;
    }
}
// »»-----► Number of lines: 25
void init_all_t_arr(t_sh *sh)
{
	char *all_operators[] = {"<<",">>","&&","||","|","<",">"};
	char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    t_func operator_handlers[] = {
		handle_heredoc,     // "<<" 0
		append_redirection, // ">>" 1
		NULL,               // "&&" 2
		NULL,               // "||" 3
		NULL,               // "|"  4
		input_redirection,  // "<"  5
		output_redirection  // ">"  6
	};
    int (*builtin_handlers[])(void *, void **) =
    {
        builtin_echo,
        builtin_cd,
        builtin_pwd,
        builtin_export,
        builtin_unset,
        builtin_env,
        builtin_exit,
        NULL
    };

	build_t_arr_dic_str(&sh->oper, all_operators, (void **)operator_handlers,sizeof(all_operators)/sizeof(char *));
    build_t_arr_dic_str(&sh->bcmd, all_builtins,  (void **)builtin_handlers,sizeof(all_builtins)/sizeof(char *));
}
