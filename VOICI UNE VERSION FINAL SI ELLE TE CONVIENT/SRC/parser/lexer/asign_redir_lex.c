/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_redir_lex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:22:52 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:31:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* extrait le nom de fichier et avance i ; NULL si manquant */
/* choisit le fname
 (inline après l'opérateur ou au token suivant) & avance *i */
static char	*take_inline_or_next(t_shell *sh, char **arr, int *i, int op_idx)
{
	char	*op;
	int		len;
	char	*fname;

	op = op_key(sh, op_idx);
	len = sh->parsed_args->len;
	if ((int)ft_strlen(arr[*i]) > (int)ft_strlen(op))
	{
		fname = arr[*i] + ft_strlen(op);
		(*i)++;
		return (fname);
	}
	if (*i + 1 < len)
	{
		fname = arr[*i + 1];
		(*i) += 2;
		return (fname);
	}
	return (NULL);
}

/* coupe sur la prochaine redirection non quotée et insère le reste 
comme nouvel arg */
static void	split_and_insert_rest(t_shell *sh, char *fname, int at_i)
{
	char	*next;
	char	*rest;

	next = next_unquoted_redir(fname);
	if (!next)
		return ;
	rest = ft_strdup(next);
	*next = '\0';
	insert_rest(sh, rest, at_i);
}

/* extrait le nom de fichier et avance i ; NULL si manquant */
char	*extract_fname(t_shell *sh, char **arr, int *i, int op_idx)
{
	char	*fname;

	fname = take_inline_or_next(sh, arr, i, op_idx);
	if (fname)
		split_and_insert_rest(sh, fname, *i);
	return (fname);
}

/* affecte le token courant si nécessaire */
void	maybe_pick_current(t_shell *sh, t_token **cur, int *cmd_idx)
{
	while (!*cur && *cmd_idx < sh->n_tokens)
	{
		if (sh->tokens[*cmd_idx].type == TOKEN_CMD
			|| sh->tokens[*cmd_idx].type == TOKEN_BCMD)
		{
			*cur = &sh->tokens[*cmd_idx];
			(*cmd_idx)++;
			return ;
		}
		(*cmd_idx)++;
	}
}

/******************assigne-redir******************** */
int	assign_redirs(t_shell *sh)
{
	t_token	*current;
	int		cmd_idx;
	int		i;
	int		ret;

	if (!sh || !sh->parsed_args || !sh->parsed_args->arr)
		return (0);
	current = NULL;
	cmd_idx = 0;
	i = 0;
	while (i < sh->parsed_args->len)
	{
		ret = assign_redirs_iter(sh, &current, &cmd_idx, &i);
		if (ret != 1)
			return (-1);
	}
	return (0);
}
