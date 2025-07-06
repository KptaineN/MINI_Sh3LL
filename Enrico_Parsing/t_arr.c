/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:08:28 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/01 15:48:48 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//array of string
size_t t_arrlen(void **arr)
{
    size_t len;

    if (!arr)
        return (0);
    
    len = 0;
    while (arr[len])
        len++;
    
    return (len);
}

/*	
	return (-1) not found
	return (%d != -1) idx of the one found in the array bcmd->arr
*/  
int is_in_t_arr_str(t_arr *arr, char *arg)
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

/*	
	For t_arr containing t_dic entries - searches by key
	return (-1) not found
	return (%d != -1) idx of the one found in the array
*/  
int is_in_t_arr_dic_str(t_arr *arr, char *arg)
{
    int i = 0;
    t_dic *dic;
    
    if (!arr || !arg)
        return (-1);
        
    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        if (dic && dic->key && strcmp((char *)dic->key, arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}

// build the dynamic array of the builtins cmd
void build_t_arr_str(t_arr **dst, char **arr_str, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(char *) * len);
    if (!(*dst)->arr)
    {
        *dst = NULL;
        return;
    }
    
    int i = 0;
    while (i < len)
    {
        (*dst)->arr[i] = ft_strdup(arr_str[i]);
        if (!(*dst)->arr[i])
        {
            *dst = NULL;
            return;
        }
        i++;
    }
}

// build the dynamic array of t_dic entries
void build_t_arr_dic_str(t_arr **dst, char **keys, void **values, int len)
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
        printf("%s\t%p\n", (char *)temp[i].key, (int*)temp[i].value);
        i++;
    }
}

// initialise the builtins and operators
void init_all_t_arr(t_shell *shell)
{
	char *all_operators[] = {"<<",">>","&&","||","|","<",">",NULL};
	char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int (*operator_handlers[])(void *, int) = {
		handle_heredoc,     // "<<"
		handle_append,      // ">>"
		handle_and,         // "&&"
		handle_or,          // "||"
		handle_pipe,        // "|"
		handle_redirect_in, // "<"
		handle_redirect_out // ">"
	};
    int (*builtin_handlers[])(void *, int) = {
        ft_echo,
        ft_cd,
        ft_pwd,
        ft_export,
        ft_unset,
        ft_env,
        ft_exit,
        NULL
    };

	build_t_arr_dic_str(&shell->oper, all_operators, (void **)operator_handlers,t_arrlen((void **)all_operators));
    build_t_arr_dic_str(&shell->bcmd, all_builtins,  (void **)builtin_handlers,t_arrlen((void **)all_builtins));
}
