/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:08:28 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/28 16:15:20 by eganassi         ###   ########.fr       */
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
int is_in_t_arr_str(t_arr *arr, const char *arg)
{
    int i = 0;
    char *key;
    while (i < arr->len)
    {
        key = (char *)((t_dic *)arr->arr[i])->key;
        if (strcmp(key, arg) == 0)
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
int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    int i = 0;
    t_dic *dic;
    int len_key;
    int len_arg;
    
    if (!arr || !arg)
        return (-1);
    
    len_arg = 1 + (arg[1]!= 0);
    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        char *str = dic->key;
        (void)str;
        len_key = strlen(dic->key);
        if (len_key<=len_arg)
        {
            if (dic && dic->key && strncmp((char *)dic->key, arg, len_key) == 0)
                return (i);
        }
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
	char *all_operators[] = {"<<",">>","&&","||","|","<",">"};
	char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int (*operator_handlers[])(void *, int) = {
		handle_heredoc,     // "<<"
		NULL,               // ">>"
		NULL,               // "&&"
		NULL,               // "||"
		NULL,               // "|"
		input_redirection, // "<"
		NULL // ">"
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

	build_t_arr_dic_str(&shell->oper, all_operators, (void **)operator_handlers,sizeof(all_operators)/sizeof(char *));
    build_t_arr_dic_str(&shell->bcmd, all_builtins,  (void **)builtin_handlers,sizeof(all_builtins)/sizeof(char *));
}
