/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_enrico.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:29:36 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/03 19:00:27 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void free_string_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_t_arr_dic_func(t_arr **arr) {
    if (!arr || !*arr) return;
    for (int i = 0; i < (*arr)->len; i++) {
        t_dic *dic = (*arr)->arr[i];
        free(dic);  // Assuming value is a function pointer, no free needed.
    }
    free((*arr)->arr);
    free(*arr);
    *arr = NULL;
}

void free_t_arr_dic(t_arr **arr) {
    if (!arr || !*arr) return;
    for (int i = 0; i < (*arr)->len; i++) {
        t_dic *dic = (*arr)->arr[i];
        free(dic->key);
        free(dic);  // Assuming value is a function pointer, no free needed.
    }
    free((*arr)->arr);
    free(*arr);
    *arr = NULL;
}

void free_t_list(t_list **env_list) {
    t_list *curr = *env_list;
    while (curr) {
        t_list *next = curr->next;
        free(curr->content);
        free(curr);
        curr = next;
    }
    *env_list = NULL;
}

void	free_family(t_sh *sh)
{
    int i = 0;
    if (!sh || !sh->f_core)
        return;
    while (sh->f_core[i])
    {
        free(sh->f_core[i]);
        i++;
    }
    free(sh->f_core);
    sh->f_core = NULL;
}

void    free_sh(t_sh *sh) {
    free_t_list(&sh->env);
    free_t_arr_dic_func(&sh->oper);
    free_t_arr_dic(&sh->bcmd);
    free_family(sh);
    free(sh);
}

