/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:32 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/08 13:43:32 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"

int		build_heredoc_fd(t_delim d, t_shell *sh);
int		prepare_heredocs(t_shell *sh);
int		apply_redirs_in_child(t_cmd *c, t_shell *sh);
void	ambiguous(const char *original);
int		is_ambiguous(const char *fname, bool quoted);
char	*expand_filename_if_needed(char *arg, t_shell *sh);
char	*remove_quotes(const char *arg);
int		run_builtin(t_cmd *c, t_shell *sh);
char	*resolve_path(const char *cmd, t_shell *sh);
char	*replace_exit_code(const char *arg, int exit_status);
char	*replace_variables(const char *arg, t_shell *sh);
int		open_and_dup_in(t_redir *r, t_shell *sh);
int		open_and_dup_out_trunc(t_redir *r, t_shell *sh);
int		open_and_dup_out_append(t_redir *r, t_shell *sh);
int		open_from_expansion(t_redir *r, t_shell *sh, int flags, int mode);
t_delim	parse_delim(const char *raw);
int		handle_heredoc(t_shell *shell, char **argv);
int		prepare_heredocs(t_shell *sh);
void	close_heredocs(t_shell *sh);

#endif // REDIR_H
