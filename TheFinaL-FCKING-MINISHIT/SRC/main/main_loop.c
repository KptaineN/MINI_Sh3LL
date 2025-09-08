/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 20:33:27 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_line_empty(const char *str)
{
	return (!str || *str == '\0');
}

int	must_exit(const char *str)
{
	return (ft_strcmp(str, "exit") == 0);
}

static int	ensure_fallback_cmd(t_shell *sh)
{
	t_list	*node;

	if (sh->n_tokens > 0 && sh->n_cmd == 0)
	{
		sh->n_cmd = 1;
		node = ft_lstnew(&sh->tokens[0]);
		if (!node)
		{
			perror("ft_lstnew");
			cleanup_shell_iter(sh, NULL);
			return (-2);
		}
		sh->cmd_head = node;
		sh->cmd_tail = node;
	}
	return (0);
}

int	parse_and_prepare(t_shell *sh, char *line)
{
	sh->input = line;
	sh->parsed_args = custom_split(line, sh);
	if (!sh->parsed_args)
		return (-1);
	attribute_token_type(sh);
	if (assign_redirs(sh) == -1)
	{
		sh->cmd_head = NULL;
		sh->cmd_tail = NULL;
		return (-1);
	}
	build_cmd_list(sh);
	if (ensure_fallback_cmd(sh) < 0)
		return (-2);
	sh->pids = malloc(sizeof(pid_t) * sh->n_cmd);
	if (!sh->pids)
	{
		perror("malloc pids");
		cleanup_shell_iter(sh, line);
		return (-2);
	}
	return (0);
}

int	read_more(char **in)
{
	bool	in_sq;
	bool	in_dq;
	size_t	i;
	int		rc;

	in_sq = false;
	in_dq = false;
	i = 0;
	quote_scan_from(*in, &i, &in_sq, &in_dq);
	while (in_sq || in_dq)
	{
		rc = read_line_step(in, &i, &in_sq, &in_dq);
		if (rc != 0)
			return (rc);
	}
	return (0);
}
