/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:47:15 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:00:04 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	add_node_advance(t_list **head, t_list **curr)
{
	if (curr == head && curr == NULL)
		return ;
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
