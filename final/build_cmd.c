/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:37:26 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/07 18:03:37 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 13
void	add_node_record(t_list **head, t_list **curr)
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
// »»-----► Number of lines: 24
static void	string_array_for_cmd(char **parsed, t_build_cmd *b)
{
	int		k;
	int		count;
	char	**arr;

	add_node_record(&b->head, &b->curr);
	count = b->i - b->j;
	if (count < 0)
		count = 0;
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
	{
		b->curr->arr_content = NULL;
		return ;
	}
	k = 0;
	while (b->j < b->i)
		arr[k++] = parsed[b->j++];
	arr[k] = NULL;
	if (parsed[b->i] && ft_strncmp(parsed[b->i], "|", 1) == 0)
	{	
		free(parsed[b->i]);
		b->j++;
	}
	b->curr->arr_content = (void **)arr;
}
// »»-----► Number of lines: 24
t_list	*build_cmd(t_sh *sh, char **parsed)
{
	t_build_cmd	b;

	ft_bzero(&b, sizeof(t_build_cmd));
	sh->n_cmd = 0;
	while (parsed[b.i])
	{
		if (ft_strcmp(parsed[b.i], "|") == 0)
		{
			if ((b.i + 1 == b.j) || b.i == 0)
				return (free_linked_list_of_array_string(b.head),NULL);
			string_array_for_cmd(parsed, &b);
			sh->n_cmd++;
		}
		b.i++;
	}
	if (ft_strncmp(parsed[b.i - 1], "|", 1) == 0)
		return (free_linked_list_of_array_string(b.head),NULL);
	string_array_for_cmd(parsed, &b);
	sh->n_cmd++;
	free(sh->parsed_args);
	return (b.head);
}
