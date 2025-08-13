/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:08:28 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 16:24:12 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t t_arrlen(void **arr)
{
    size_t len = 0;
    if (!arr)
        return 0;
    while (arr[len])
        len++;
    return len;
}

int is_in_t_arr_str(t_arr *arr, const char *arg)
{
    if (!arr || !arr->arr || !arg)
        return -1;
    for (int i = 0; i < arr->len; i++)
    {
        t_dic *dic = (t_dic *)arr->arr[i];
        if (!dic || !dic->key)
            continue;
        if (ft_strcmp(dic->key, arg) == 0)
            return i;
    }
    return -1;
}

int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    if (!arr || !arr->arr || !arg)
        return -1;

    for (int i = 0; i < arr->len; i++)
    {
        t_dic *dic = (t_dic *)arr->arr[i];
        if (!dic || !dic->key)
            continue;
        size_t len_key = ft_strlen(dic->key);
        if (ft_strncmp(dic->key, arg, len_key) == 0)
            return i;
    }
    return -1;
}


void build_t_arr_str(t_arr **dst, char **arr_str, int len)
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
            free(*dst);
            *dst = NULL;
            return;
        }
        i++;
    }
}

void build_t_arr_dic_str(t_arr **dst, char **keys,  int (**values)(t_shell *, char **), int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);
    if (!(*dst)->arr) {
        free(*dst);
        *dst = NULL;
        return;
    }
    for (int i = 0; i < len; i++)
    {
        t_dic *dic = malloc(sizeof(t_dic));
        if (!dic)
        {
            int j = 0;
            while (j < i)
            {
                t_dic *prev = (t_dic *)(*dst)->arr[j];
                free(prev->key);
                free(prev);
                j++;
            }
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        dic->key = ft_strdup(keys[i]);
        dic->value = values[i];
        if (!dic->key)
        {
            free(dic);
            int j = 0;
            while (j < i)
            {
                t_dic *prev = (t_dic *)(*dst)->arr[j];
                free(prev->key);
                free(prev);
                j++;
            }
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        (*dst)->arr[i] = dic;
    }
}

/*
    Initialise tous les builtins et opérateurs dans la shell (via bcmd et oper)
*/
void init_all_t_arr(t_shell *shell)
{
    char *all_operators[] = {"<<", ">>", "&&", "||", "|", "<", ">"};
    char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int (*operator_handlers[])(t_shell *, char **) = {
        handle_heredoc,
        handle_append,
        handle_and,
        handle_or,
        handle_pipe,
        handle_redirect_in,
        handle_redirect_out 
    };
    int (*builtin_handlers[])(t_shell *, char **) = {
        ft_echo,
        ft_cd,
        ft_pwd,
        ft_export,
        ft_unset,
        ft_env,
        ft_exit,
    };
    int n_operateurs = sizeof(all_operators) / sizeof(char *);
    int n_builtins = sizeof(all_builtins) / sizeof(char *);

    build_t_arr_dic_str(&shell->oper, all_operators, operator_handlers, n_operateurs);
    build_t_arr_dic_str(&shell->bcmd, all_builtins, builtin_handlers, n_builtins);
}
