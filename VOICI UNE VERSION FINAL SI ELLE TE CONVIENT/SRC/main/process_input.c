/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:28:52 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:02:43 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Contrat identique à ta version.
** Codes possibles retournés par process_input :
** 0, 1, 2 ou un <0 venant de parse_and_prepare.
 Regroupe les sorties précoces: qres == -1 / -2, ou ligne vide */
static bool	handle_qres_or_empty(t_shell *sh, char **pin, int qres, int *ret)
{
	if (qres == -1)
	{
		free(*pin);
		sh->exit_status = 2;
		g_exit_status = sh->exit_status;
		*ret = 0;
		return (true);
	}
	if (qres == -2)
	{
		free(*pin);
		*ret = 0;
		return (true);
	}
	if (is_line_empty(*pin))
	{
		cleanup_shell_iter(sh, *pin);
		*ret = 0;
		return (true);
	}
	return (false);
}

static bool	early_stage(t_shell *sh, char **pin, int *out_ret)
{
	int	qres;

	qres = read_more(pin);
	if (handle_qres_or_empty(sh, pin, qres, out_ret))
		return (true);
	add_history(*pin);
	if (must_exit(*pin))
	{
		cleanup_shell_iter(sh, *pin);
		*out_ret = 1;
		return (true);
	}
	return (false);
}

bool	expand_stage(t_shell *sh, char *in, char **out_line, int *out_ret)
{
	char	*line;

	line = expand_input(in, sh);
	if (!line)
	{
		cleanup_shell_iter(sh, in);
		*out_ret = 0;
		return (true);
	}
	*out_line = line;
	return (false);
}

bool	parse_stage(t_shell *sh, char *line, char *in, int *out_ret)
{
	int	ret;

	ret = parse_and_prepare(sh, line);
	if (ret < 0)
	{
		cleanup_shell_iter(sh, line);
		sh->input = NULL;
		free(in);
		g_exit_status = sh->exit_status;
		*out_ret = ret;
		return (true);
	}
	return (false);
}

int	process_input(t_shell *sh, char *in)
{
	char	*line;
	int		ret;

	if (early_stage(sh, &in, &ret))
		return (ret);
	if (expand_stage(sh, in, &line, &ret))
		return (ret);
	if (parse_stage(sh, line, in, &ret))
		return (ret);
	return (run_stage(sh, line, in));
}
