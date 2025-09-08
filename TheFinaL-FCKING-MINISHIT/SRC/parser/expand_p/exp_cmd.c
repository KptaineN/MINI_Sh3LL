/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:05:44 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 19:22:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	should_skip_first(t_token *token)
{
	int						nb_args;
	t_subtoken_container	*c;
	t_subtoken				*p;
	int						len;

	if (!token || !token->cmd_args_parts)
		return (0);
	nb_args = token->n_args;
	if (nb_args <= 0)
		return (0);
	c = &token->cmd_args_parts[0];
	if (c->n_parts != 1)
		return (0);
	p = &c->parts[0];
	len = (int)ft_strlen(token->value);
	if (p->len == len && ft_strncmp(p->p, token->value, p->len) == 0)
		return (1);
	return (0);
}

int	fill_expanded_args(t_token *tok, t_list *env, char **res, int skip_first)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!skip_first)
	{
		res[j] = ft_strdup(tok->value);
		if (!res[j])
			return (-1);
		j++;
	}
	while (i < tok->n_args)
	{
		res[j] = expand_container(&tok->cmd_args_parts[i], NULL, env);
		if (!res[j])
			return (-1);
		i++;
		j++;
	}
	res[j] = NULL;
	return (0);
}

char	**expand_cmd(t_token *token, t_list *env)
{
	int		skip_first;
	int		argc_final;
	char	**res;

	if (!token || !token->cmd_args_parts)
		return (NULL);
	skip_first = should_skip_first(token);
	if (skip_first)
		argc_final = token->n_args;
	else
		argc_final = token->n_args + 1;
	res = malloc(sizeof(char *) * (argc_final + 1));
	if (!res)
		return (NULL);
	if (fill_expanded_args(token, env, res, skip_first) < 0)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
