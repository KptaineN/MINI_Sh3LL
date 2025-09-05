/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:37:26 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/05 16:13:08 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

typedef struct s_cmdctx
{
	t_sh	*sh;
	char	**parsed;
	int		i;
	int		j;
	t_list	*head;
	t_list	*curr;
}			t_cmdctx;

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

/* fix structure au lieu de 5argu*/
static void	string_array_for_cmd_ctx(t_cmdctx *c)
{
	int		k;
	int		count;
	char	**arr;

	add_node_record(&c->head, &c->curr);
	count = c->i - c->j;
	if (count < 0)
		count = 0;
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
	{
		c->curr->arr_content = NULL;
		return ;
	}
	k = 0;
	while (c->j < c->i)
		arr[k++] = c->parsed[c->j++];
	arr[k] = NULL;
	if (c->parsed[c->i] && ft_strncmp(c->parsed[c->i], "|", 1) == 0)
		c->j++;
	c->curr->arr_content = (void **)arr;
}

/**
t_list	*build_cmd(t_sh *sh, char **parsed)
{
	int		i;
	int		j;
	t_list	*head;
	t_list	*curr;

	i = 0;
	j = 0;
	head = NULL;
	curr = NULL;
	sh->n_cmd = 0;
	while (parsed[i])
	{
		if (ft_strncmp(parsed[i], "|", 1) == 0)
		{
			if ((i + 1 == j && i != 0) || i == 0)
				perror("parsing: starting with pipe or concatenating pipes");
			string_array_for_cmd(parsed, &i, &j, &head, &curr);
			sh->n_cmd++;
		}
		i++;
	}
	if (ft_strncmp(parsed[i - 1], "|", 1) == 0)
		perror("parsing: finishing with a pipe");
	string_array_for_cmd(parsed, &i, &j, &head, &curr);
	sh->n_cmd++;
	// display_linked_list_of_string_array(head);
	return (head);
}*/
/*********build_cmd ******** */
/* Contexte pour éviter 5 arguments à chaque appel */
static int	is_pipe_tok(const char *s)
{
	return (s && ft_strncmp(s, "|", 1) == 0);
}

/* Envoie le segment courant dans la liste et compte une commande */
static void	flush_current_segment(t_cmdctx *c)
{
	string_array_for_cmd_ctx(c);
	c->sh->n_cmd++;
}

/* Parcourt le tableau et “flushe” à chaque pipe rencontré */
static void	scan_segments(t_cmdctx *c)
{
	while (c->parsed[c->i])
	{
		if (is_pipe_tok(c->parsed[c->i]))
		{
			if ((c->i + 1 == c->j && c->i != 0) || c->i == 0)
				perror("parsing: starting with pipe or concatenating pipes");
			flush_current_segment(c);
		}
		c->i++;
	}
}

/* Optionnel : avertit si on finit par un pipe */
static void	warn_trailing_pipe(t_cmdctx *c)
{
	if (c->i > 0 && is_pipe_tok(c->parsed[c->i - 1]))
		perror("parsing: finishing with a pipe");
}

/* API */
t_list	*build_cmd(t_sh *sh, char **parsed)
{
	t_cmdctx	c;

	c.sh = sh;
	c.parsed = parsed;
	c.i = 0;
	c.j = 0;
	c.head = NULL;
	c.curr = NULL;
	sh->n_cmd = 0;
	if (!parsed || !parsed[0])
		return (NULL);
	scan_segments(&c);
	warn_trailing_pipe(&c);
	flush_current_segment(&c);
	free(sh->parsed_args);
	sh->parsed_args = NULL;
	return (c.head);
}
/* *********build_cmd ******** */