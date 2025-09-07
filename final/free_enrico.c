/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_enrico.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:29:36 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 20:05:17 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 11
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
// »»-----► Number of lines: 9
void free_t_arr_dic_handler(t_arr **arr)
{
    if (!arr || !*arr) return;
    for (int i = 0; i < (*arr)->len; i++) {
        t_dic *dic = (*arr)->arr[i];    
        free(dic->key);
    }
    free((*arr)->arr[0]);
    free((*arr)->arr);
    free(*arr);
    *arr = NULL;
}
// »»-----► Number of lines: 8
void free_t_linked_dic_env(t_list **env_list)
{
    t_list *curr = *env_list;
    t_dic *dic;
    while (curr) {
        t_list *next = curr->next;
        dic = (t_dic *)curr->content;
        free(dic->key);
        free(dic->value);
        free(dic);
        free(curr);
        curr = next;
    }
    *env_list = NULL;
}
// »»-----► Number of lines: 10
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
// »»-----► Number of lines: 5
void    free_sh(t_sh *sh)
{
    free(sh->msg_error);
    free_t_linked_dic_env(&sh->env);
    free_t_arr_dic_handler(&sh->oper);
    free_t_arr_dic_handler(&sh->bcmd);
    free_family(sh);
    free(sh);
}
// »»-----► Number of lines: 17
void free_linked_list_of_array_string(t_list* head)
{
    t_list* current = head;
    t_list* next;

    while (current != NULL) {

        if (current->arr_content != NULL) {
            for (int i = 0; current->arr_content[i]; i++) {
                if (current->arr_content[i] != NULL) {
                    free(current->arr_content[i]);
                }
            }
            free(current->arr_content);
        }
        next = current->next;
        free(current);
        current = next;
    }
}

void free_setnull(void **a)
{
    if (!a || !*a)
        return;
    free(*a);
    *a = NULL;
}
