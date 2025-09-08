/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:29:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 12:29:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* helpers locaux */

static void	free_tmp_partial(char **tmp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

static void	free_tmp_full(char **tmp, int n_parts)
{
	int	i;

	i = 0;
	while (i < n_parts)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

static char	**build_tmp_parts(const t_subtoken_container *a,
		t_shell *sh, int *out_total)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * a->n_parts);
	if (!tmp)
		return (NULL);
	*out_total = 0;
	i = 0;
	while (i < a->n_parts)
	{
		if (a->parts[i].type == QUOTE_SINGLE)
			tmp[i] = ft_strdup(a->parts[i].p);
		else if (a->parts[i].type == QUOTE_DBL || a->parts[i].type == QUOTE_N)
			tmp[i] = replace_variables(a->parts[i].p, sh);
		else
			tmp[i] = ft_strdup(a->parts[i].p);
		if (!tmp[i])
			return (free_tmp_partial(tmp, i), NULL);
		*out_total += (int)ft_strlen(tmp[i]);
		i++;
	}
	return (tmp);
}

static char	*join_tmp_into_out(const t_subtoken_container *a,
		char **tmp, int total)
{
	char	*out;
	int		i;
	int		pos;
	size_t	len;

	out = (char *)malloc((size_t)total + 1);
	if (!out)
		return (free_tmp_full(tmp, a->n_parts), NULL);
	pos = 0;
	i = 0;
	while (i < a->n_parts)
	{
		len = ft_strlen(tmp[i]);
		ft_memcpy(out + pos, tmp[i], len);
		pos += (int)len;
		free(tmp[i]);
		i++;
	}
	out[total] = '\0';
	free(tmp);
	return (out);
}

/* orchestrateur */
char	*expand_container(t_subtoken_container *a, t_list **head, t_list *env)
{
	char	**tmp;
	char	*out;
	t_shell	sh;
	int		total;

	(void)head;
	if (!a || !a->parts || a->n_parts <= 0)
		return (ft_strdup(""));
	ft_bzero(&sh, sizeof(t_shell));
	sh.env = env;
	sh.exit_status = g_exit_status;
	tmp = build_tmp_parts(a, &sh, &total);
	if (!tmp)
		return (NULL);
	out = join_tmp_into_out(a, tmp, total);
	return (out);
}
