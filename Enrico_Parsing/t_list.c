/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:01:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/10 10:42:24 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*set_linked_path(char **env)
{
	t_list	*head;
	t_list	*node;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = ft_lstnew(strdup(env[i]));
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

static int count_linked(t_list *node)
{
	int count = 1;
	t_list *first = node;
	if (!node)
		return 0;
	node = node->next;
	while (node != first)
	{
		count++;
		node = node->next ; 
	}
	return count;
}

char **linked_to_array_string(t_list *node)
{
	t_list *first = node;
	int len = count_linked(node);
	char **arr = malloc(sizeof(char *)*(len+1));
	arr[len] = 0;
	int i = 0;

	while(i<len)
	{
		arr[i] = node->content;
		node = node->next;
		i++;
	}
	node = first;
	return arr;
}
