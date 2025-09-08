/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:46:42 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:52:24 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* commande → avance de n_args comme dans la version d'origine */
int	advance_after_command(t_shell *sh, int i)
{
	int	n_args;

	n_args = count_args_cmd(sh, i);
	return (i + n_args);
}

/* opérateur → avance l'index comme dans la version d'origine */
int	count_tokens(t_shell *sh, t_arr *parsed_args, t_arr *oper)
{
	char	**args;
	int		count;
	int		i;
	int		op_idx;

	if (!parsed_args || !parsed_args->arr)
		return (0);
	args = (char **)parsed_args->arr;
	count = 0;
	i = 0;
	while (i < parsed_args->len)
	{
		op_idx = is_in_t_arr_dic_str(oper, args[i]);
		if (op_idx != -1)
		{
			count++;
			i = advance_after_operator(sh, parsed_args, i, op_idx);
		}
		else
		{
			count++;
			i = advance_after_command(sh, i);
		}
	}
	return (count);
}

int	setup_tokens_or_return(t_shell *sh)
{
	if (!sh || !sh->parsed_args || !sh->parsed_args->arr)
	{
		if (sh)
			sh->n_tokens = 0;
		return (1);
	}
	if (sh->parsed_args->len <= 0)
	{
		sh->n_tokens = 0;
		return (1);
	}
	sh->n_tokens = count_tokens(sh, sh->parsed_args, sh->oper);
	sh->tokens = (t_token *)calloc(sh->n_tokens, sizeof(t_token));
	if (!sh->tokens)
	{
		perror("Erreur allocation tokens");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	process_cmd_or_bcmd(t_shell *sh, t_token *tok, int i)
{
	char	**args;
	int		nb_args;
	int		new_i;

	args = (char **)sh->parsed_args->arr;
	if (is_in_t_arr_str(sh->bcmd, args[i]) != -1)
		tok->type = TOKEN_BCMD;
	else
		tok->type = TOKEN_CMD;
	nb_args = count_args_cmd(sh, i);
	if (!(nb_args > 0))
		nb_args = 1;
	new_i = attribute_cmd_subtokens(sh, tok, i, nb_args);
	new_i = skip_trailing_redirs(sh, args, new_i);
	if (new_i > i)
		return (new_i);
	else
		return (i + 1);
}
