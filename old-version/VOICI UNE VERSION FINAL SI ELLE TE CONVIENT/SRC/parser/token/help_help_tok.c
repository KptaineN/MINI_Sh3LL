/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_help_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:52:40 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 14:08:25 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* calcule la longueur de l'opérateur de redirection au début d'arg */
size_t	redir_op_len(const char *arg)
{
	size_t	op_len;

	if (arg[0] == '<' && arg[1] == '<')
		op_len = 2;
	else if (arg[0] == '>' && arg[1] == '>')
		op_len = 2;
	else
		op_len = 1;
	return (op_len);
}

/* alloue op et fname à partir de arg/op_len, exit en cas d'échec */
static void	build_op_and_fname(const char *arg, size_t op_len,
		char **op, char **fname)
{
	*fname = ft_strdup(arg + op_len);
	*op = ft_substr(arg, 0, op_len);
	if (!*fname || !*op)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

/* ---------- insert_filename  ---------- */
void	insert_filename(t_shell *sh, int i, char *fname)
{
	char	**src;
	char	**dst;
	int		len;

	src = (char **)sh->parsed_args->arr;
	len = sh->parsed_args->len;
	dst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(dst, *src, sizeof(char *) * (i + 1));
	dst[i + 1] = fname;
	ft_memcpy(dst + (i + 2), *(src + (i + 1)),
		sizeof(char *) * (len - (i + 1)));
	free(sh->parsed_args->arr);
	sh->parsed_args->arr = (void **)dst;
	sh->parsed_args->len = len + 1;
}

/* ---------- split_inline_redir_if_needed (≤ 25 lignes) ---------- */
int	split_inline_redir_if_needed(t_shell *sh, int i,
		bool *restart, int *out_i)
{
	char	**args;
	size_t	op_len;
	char	*op;
	char	*fname;

	args = (char **)sh->parsed_args->arr;
	if (!(args[i][0] == '<' || args[i][0] == '>'))
		return (0);
	op_len = redir_op_len(args[i]);
	if (ft_strlen(args[i]) <= op_len)
		return (0);
	build_op_and_fname(args[i], op_len, &op, &fname);
	free(args[i]);
	args[i] = op;
	insert_filename(sh, i, fname);
	if (restart)
		*restart = true;
	*out_i = i + 1;
	return (1);
}
