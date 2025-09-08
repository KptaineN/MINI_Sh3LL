/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:27 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 14:00:46 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	is_redir_op_idx(int op_idx)
{
	return (op_idx < 2 || op_idx > 4);
}

static int	skip_redir_token(t_shell *sh, char **arr, int i, int op_idx)
{
	t_dic	*d;

	d = (t_dic *)sh->oper->arr[op_idx];
	if ((int)ft_strlen(arr[i]) == (int)ft_strlen(d->key))
		i++;
	i++;
	return (i);
}

int	skip_trailing_redirs(t_shell *sh, char **args, int i)
{
	int	op_idx;

	while (i < sh->parsed_args->len)
	{
		op_idx = is_in_t_arr_dic_str(sh->oper, args[i]);
		if (op_idx != -1 && is_redir_op_idx(op_idx))
			i = skip_redir_token(sh, args, i, op_idx);
		else
			break ;
	}
	return (i);
}

int	process_tokens_once(t_shell *sh)
{
	char	**args;
	int		i;
	int		idx;
	bool	restart;

	args = (char **)sh->parsed_args->arr;
	i = 0;
	idx = 0;
	restart = false;
	while (i < sh->parsed_args->len && idx < sh->n_tokens)
	{
		token_set_value_or_die(&sh->tokens[idx], args, i);
		if (is_operator_here(sh, args, i))
			i = process_operator_token(sh, &sh->tokens[idx], i, &restart);
		else
			i = process_cmd_or_bcmd(sh, &sh->tokens[idx], i);
		if (restart)
			break ;
		idx++;
	}
	if (restart)
		return (1);
	return (0);
}

void	attribute_token_type(t_shell *sh)
{
	int	restart;

	while (1)
	{
		if (setup_tokens_or_return(sh))
			return ;
		restart = process_tokens_once(sh);
		if (!restart)
			break ;
		free_tokens(sh);
	}
}
