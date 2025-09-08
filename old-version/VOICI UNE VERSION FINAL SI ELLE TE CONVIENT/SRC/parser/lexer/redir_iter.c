/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:34:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:34:46 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*next_unquoted_redir(char *s)
{
	int		j;
	bool	in_sq;
	bool	in_dq;

	j = 0;
	in_sq = false;
	in_dq = false;
	while (s[j])
	{
		if (s[j] == '\'' && !in_dq && escape_check(s, j))
			in_sq = !in_sq;
		else if (s[j] == '"' && !in_sq && escape_check(s, j))
			in_dq = !in_dq;
		else if (!in_sq && !in_dq && (s[j] == '<' || s[j] == '>'))
			return (s + j);
		j++;
	}
	return (NULL);
}

/* --- helpers --- */
int	handle_no_operator(t_shell *sh, t_token **current, int *cmd_idx,
		int *i)
{
	maybe_pick_current(sh, current, cmd_idx);
	(*i)++;
	return (1);
}

static int	handle_redir(t_shell *sh, t_token **current, int *i, int op_idx)
{
	char	**arr;
	char	*fname;

	arr = (char **)sh->parsed_args->arr;
	fname = extract_fname(sh, arr, i, op_idx);
	if (!fname || *fname == '\0')
		return (report_missing_fname(sh));
	push_redir_if_current(*current, op_idx, fname);
	return (1);
}

static void	handle_pip(t_token **current, int *cmd_idx)
{
	*current = NULL;
	(*cmd_idx)++;
}

/* --- orchestrateur --- */

int	assign_redirs_iter(t_shell *sh, t_token **current, int *cmd_idx, int *i)
{
	char	**arr;
	int		op_idx;

	arr = (char **)sh->parsed_args->arr;
	op_idx = is_in_t_arr_dic_str(sh->oper, arr[*i]);
	if (op_idx == -1)
		return (handle_no_operator(sh, current, cmd_idx, i));
	if (is_redir_op(op_idx))
	{
		if (!*current)
			maybe_pick_current(sh, current, cmd_idx);
		return (handle_redir(sh, current, i, op_idx));
	}
	if (op_idx == 4)
		handle_pip(current, cmd_idx);
	(*i)++;
	return (1);
}
