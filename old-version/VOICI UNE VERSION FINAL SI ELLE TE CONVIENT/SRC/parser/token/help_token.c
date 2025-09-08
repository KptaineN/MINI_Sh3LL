/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:18:05 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 14:09:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_set_value_or_die(t_token *tok, char **args, int i)
{
	tok->value = ft_strdup(args[i]);
	if (!tok->value)
	{
		perror("Erreur allocation token value");
		exit(EXIT_FAILURE);
	}
}

int	is_operator_here(t_shell *sh, char **args, int i)
{
	if (!args[i])
		return (0);
	if (is_in_t_arr_dic_str(sh->oper, args[i]) != -1)
		return (1);
	return (args[i][0] == '<' || args[i][0] == '>');
}

/* ---------- helper: si token[i] est une redirection connue,
 saute le filename ---------- */
static int	maybe_skip_fname_after_redir(t_shell *sh, int i)
{
	char	**args;
	int		op_idx;
	t_dic	*d;

	args = (char **)sh->parsed_args->arr;
	op_idx = is_in_t_arr_dic_str(sh->oper, args[i]);
	if (op_idx != -1 && (op_idx < 2 || op_idx > 4))
	{
		d = (t_dic *)sh->oper->arr[op_idx];
		if ((int)ft_strlen(args[i]) == (int)ft_strlen(d->key))
			return (i + 2);
	}
	return (i + 1);
}

/* ---------- orchestrateur ---------- */
int	process_operator_token(t_shell *sh, t_token *tok, int i, bool *restart)
{
	int		handled;
	int		next_i;

	tok->type = TOKEN_OPER;
	handled = split_inline_redir_if_needed(sh, i, restart, &next_i);
	if (handled)
		return (next_i);
	return (maybe_skip_fname_after_redir(sh, i));
}

int	advance_after_operator(t_shell *sh, t_arr *parsed_args, int i, int op_idx)
{
	int	consumed;

	if (op_idx < 2 || op_idx > 4)
	{
		consumed = file_access_redirection(sh, parsed_args->arr, op_idx, i);
		return (i + consumed);
	}
	return (i + 1);
}
