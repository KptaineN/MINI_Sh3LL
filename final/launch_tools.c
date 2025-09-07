/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:48:34 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 20:08:45 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_list *search_env(t_list *lst, const char *target)
{
    t_dic *dic;

    if (!lst | !target)
        return NULL;

    while (lst)
    {
        dic = (t_dic *)lst->content;
        if (dic->key && strcmp(dic->key, target) == 0)
            return lst;
        lst = lst->next;
    }
    return NULL;
}

static void ft_lstadd_front(t_list **lst, void *content)
{
    t_list *new_node;

    if (!lst || !content)
        return;

    // Allocate new node
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return; // Allocation failure

    // Duplicate content (assumes char *)
    new_node->content = (void *)ft_strdup((char *)content);
    if (!new_node->content)
    {
        free(new_node);
        return; // Allocation failure
    }

    // Link new node to current head
    new_node->next = *lst;
    *lst = new_node; // Update head to new node
}


void replace_or_add(t_list **lst, const char *old, const char *new)
{
    t_list *node;
    t_dic *dic;
    char *newval;

    if (!*lst || !old || !new)
        return;
    
    // Search for node matching old
    node = search_env(*lst, old);
    newval = ft_strdup(new);
    if (node)
    {
        dic = (t_dic *)node->content;
        free(dic->value);
        dic->value = newval;        
        return;
    }
    else
    {
        dic = malloc(sizeof(t_dic));
        dic->key = ft_strdup(old);
        dic->key = newval;
    }
    ft_lstadd_front(lst, (void *)dic);
}

void add_env(t_sh *sh, const char *key, int fd)
{
    char s[6];
    ssize_t n = read(fd, s,sizeof(s));
    s[n] = 0;
    replace_or_add(&sh->env, key, (const char *)s);
}

void send_pid(int fd, int pid)
{
    char *s_pid = ft_itoa(pid);
    write(fd, s_pid, ft_strlen(s_pid));  // Send child's PID to child
    write(fd,"\0",1);
    free(s_pid);
}

