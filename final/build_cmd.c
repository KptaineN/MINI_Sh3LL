/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:37:26 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/06 09:46:45 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

// »»-----► Number of lines: 13
static void	add_node_record(t_list **head, t_list **curr)
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
// »»-----► Number of lines: 21
static void	string_array_for_cmd_ctx(t_sh *sh, t_build_cmd *b)
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
		arr[k++] = sh->parsed_args[b->j++];
	arr[k] = NULL;
	if (sh->parsed_args[b->i] && ft_strncmp(sh->parsed_args[b->i], "|", 1) == 0)
		b->j++;
	b->curr->arr_content = (void **)arr;
}
// »»-----► Number of lines: 19
t_list	*build_cmd(t_sh *sh, char **parsed)
{
	t_build_cmd	b;

	ft_bzero(&b, sizeof(t_build_cmd));
	sh->n_cmd = 0;
	while (parsed[b.i])
	{
		if (ft_strncmp(parsed[b.i], "|", 1) == 0)
		{
			if ((b.i + 1 == b.j && b.i != 0) || b.i == 0)
				perror("parsing: starting with pipe or concatenating pipes");
			string_array_for_cmd(parsed, &b);
			sh->n_cmd++;
		}
		b.i++;
	}
	if (ft_strncmp(parsed[b.i - 1], "|", 1) == 0)
		perror("parsing: finishing with a pipe");
	string_array_for_cmd(parsed, &b);
	sh->n_cmd++;
	// display_linked_list_of_string_array(head);
	return (b.head);
}
