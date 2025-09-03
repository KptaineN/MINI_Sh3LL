/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:37:26 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/02 18:40:57 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void add_node_record(t_list **head, t_list **curr)
{
    if (curr == head && curr == NULL)
        return;
    if (*curr == NULL)
    {   
        *head = malloc(sizeof(t_list));
        (*curr) = *head;
    }
    else
    {    
        (*curr)->next = malloc(sizeof(t_list));
        (*curr) = (*curr)->next;
    }
    (*curr)->next = NULL;
}

void string_array_for_cmd(char **parsed, int *i, int *j, t_list **head, t_list **curr)
{
    int k;
    char **arr;
    arr = malloc(sizeof(char *)*((*i)-(*j)+1));
    add_node_record(head,curr);
    k = 0;
    while(*j<*i)
        arr[k++] = parsed[(*j)++]; 
    arr[k] = 0;
    (*j)++;
    (*curr)->arr_content = (void **)arr;
}

t_list *build_cmd(t_sh *sh, char **parsed)
{
    int i = 0;
    int j = 0;

    t_list *head = NULL;
    t_list *curr = NULL;
    sh->n_cmd = 0;
    while(parsed[i])
    {
        if (ft_strncmp(parsed[i],"|",1) == 0)
        {
            if ((i+1 == j && i != 0) || i == 0)
                perror("parsing: starting with pipe or concatenating pipes");
            string_array_for_cmd(parsed,&i,&j,&head,&curr);
            sh->n_cmd++;
        }
        i++;   
    }
    if (ft_strncmp(parsed[i-1],"|",1) == 0) 
        perror("parsing: finishing with a pipe");
    string_array_for_cmd(parsed,&i,&j,&head,&curr);
    sh->n_cmd++;
    //display_linked_list_of_string_array(head);
    return head;
}
