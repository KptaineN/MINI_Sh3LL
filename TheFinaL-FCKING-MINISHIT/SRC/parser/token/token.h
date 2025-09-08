/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:19:01 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 20:04:51 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../../../include/minishell.h"

typedef struct s_subtoken_part
{
	char		*p;
	int			type;
}				t_subtoken_part;

typedef struct s_qstate
{
	bool		in_sq;
	bool		in_dq;
	bool		in_nq;
	int			count;
}				t_qstate;

typedef struct s_it
{
	int			idx;
	int			k;
}				t_it;

typedef struct s_stctx
{
	const char	*arg;
	int			arg_len;
	int			idx;
	int			i;
	t_subtoken	*parts;
}				t_stctx;

int				count_subtokens(const char *str);
int				subtoken_of_cmd(t_subtoken_container *container, char *arg);
int				attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token,
					int idx, int len);
void			token_set_value_or_die(t_token *tok, char **args, int i);
int				is_operator_here(t_shell *sh, char **args, int i);
int				process_operator_token(t_shell *sh, t_token *tok, int i,
					bool *restart);
int				advance_after_operator(t_shell *sh, t_arr *parsed_args, int i,
					int op_idx);
int				advance_after_command(t_shell *sh, int i);
void			reset_container(t_subtoken_container *c);
void			free_parts_prefix(t_subtoken_part *parts, int n);
int				stctx_init(t_stctx *st, t_subtoken_container *c, char *arg);
void			stctx_step(t_stctx *st);
int				validate_last_or_fail(t_subtoken_container *c, t_stctx *st);
void			handle_single_quoted(t_stctx *st);
void			handle_double_quoted(t_stctx *st);
void			handle_unquoted(t_stctx *st);
void			insert_filename(t_shell *sh, int i, char *fname);
int				split_inline_redir_if_needed(t_shell *sh, int i,
					bool *restart, int *out_i);
int				setup_tokens_or_return(t_shell *sh);
int				process_cmd_or_bcmd(t_shell *sh, t_token *tok, int i);
int				skip_trailing_redirs(t_shell *sh, char **args, int i);

#endif // TOKEN_H