/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:48:34 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/04 12:39:03 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_list *search_lst(t_list *lst, const char *target)
{
    size_t target_len;

    if (!lst || !target)
        return NULL;

    target_len = strlen(target);

    while (lst)
    {
        char *s  = (char *)lst->content;
        (void)s;
        if (lst->content && strncmp((char *)lst->content, target, target_len) == 0)
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

    if (!*lst || !old || !new)
        return;

    // Search for node matching old
    node = search_lst(*lst, old);
    if (node)
    {
        // Match found: free old content and replace
        free(node->content);
        node->content = ft_strdup(new);
        if (!node->content)
        {
            // Handle strdup failure (optional: remove node or set to NULL)
            node->content = NULL;
        }
        return;
    }

    // No match: add new node at front
    ft_lstadd_front(lst, (void *)new);
}

void add_env(t_sh *sh, const char *key ,int fd)
{
    char s[20] = {0};
    ssize_t l_k  = ft_strlen(key);
    ssize_t n = read(fd, s, l_k + sizeof(pid_t));
    if (n != (l_k + (ssize_t)sizeof(pid_t)))
    {
        perror("add_pid_func");
        return;  // Or handle error as needed
    }
    pid_t received_pid = *(pid_t *)(&s[4]);  // Extract binary PID
    ft_itoa_inplace(&s[4], (int)received_pid);
    replace_or_add(&sh->env, key, (const char *)s);
}

void send_pid(int fd, int pid)
{
    char *s_pid = ft_itoa(pid);
    write(fd, "PID=", 4);
    write(fd, s_pid, ft_strlen(s_pid));  // Send child's PID to child
    free(s_pid);
}

