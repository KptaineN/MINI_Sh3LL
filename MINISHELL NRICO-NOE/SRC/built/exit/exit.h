/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:30:36 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 18:40:21 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "../../../include/minishell.h"

typedef struct s_ctx
{
	bool		in_sq;
	bool		in_dq;
	size_t		i;
	size_t		j;
}				t_stx;

typedef struct s_rep
{
	const char	*code;
	size_t		clen;
}				t_rep;

char			*replace_exit_code(const char *input, int code);
size_t			count_exit_patterns(const char *s);
char			*fill_with_replacement(const char *input, const char *code_str,
					size_t out_len);
int				is_numeric(const char *str);
int				builtin_exit(t_shell *shell, char **argv);
size_t			compute_out_len(size_t input_len, size_t count,
					size_t code_len);
void			update_quotes(bool *in_sq, bool *in_dq, char c);
void			ctx_init(t_stx *c);
int				try_quote(const char *s, t_stx *c, char *out);
int				try_exit(const char *s, t_stx *c, char *out, t_rep *r);

#endif // EXIT_H
