/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:46:58 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 13:54:41 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 13
t_list *search_env_node(t_list *lst, const char *target)
{
    t_dic *dic;

    if (!lst | !target)
        return NULL;

    while (lst)
    {
        dic = (t_dic *)lst->content;
        if (dic->key && ft_strcmp(dic->key, target) == 0)
            return lst;
        lst = lst->next;
    }
    return NULL;
}
// »»-----► Number of lines: 11
char *get_env_value(t_list *env_list, const char *key)
{
    t_list *current = env_list;
    t_dic *dic;

    while (current)
    {
        dic = (t_dic *)current->content;
        if (dic->key && ft_strcmp(dic->key, key) == 0)
            return (dic->value);
        current = current->next;
    }
    return (NULL);
}
// »»-----► Number of lines: 25
void replace_or_add(t_list **lst, const char *key, const char *value)
{
    t_list *node;
    t_dic *dic;
    char *newval;

    if (!*lst || !key || !value)
        return;
    node = search_env_node(*lst, key);
    newval = ft_strdup(value);
    if (node)
    {
        dic = (t_dic *)node->content;
        free(dic->value);
        dic->value = (void *)newval;        
        return;
    }
    else
    {
        node = malloc(sizeof(t_list));
        dic = malloc(sizeof(t_dic));
        dic->key =   (void*)ft_strdup(key);
        dic->value = (void*)newval;
        node->content = (void *)dic;
        node->next = (*lst);
        *lst = node;
    }
}

