/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 16:50:55 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


static char *strip_quotes(const char *s)
{
    size_t len;

    if (!s)
        return NULL;
    len = ft_strlen(s);
    if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"') || (s[0] == '\'' && s[len - 1] == '\'')))
        return ft_substr(s, 1, len - 2);
    return ft_strdup(s);
}

int file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i)
{
    char    *token;
    char    *op;
    int     consumed;

    (void)shell;
    token = (char *)arr[i];
    op = ((t_dic *)shell->oper->arr[t_arr_index])->key;
    consumed = 1;
    if ((int)ft_strlen(token) == (int)ft_strlen(op))
        consumed = 2;
    return consumed;
}

void add_redir(t_token *tok, t_rtype type, const char *arg)
{
    t_redir *new_r;

    new_r = realloc(tok->r, sizeof(t_redir) * (tok->r_count + 1));
    if (!new_r)
        return;
    tok->r = new_r;
    tok->r[tok->r_count].type = type;
    if (type == R_HEREDOC)
        tok->r[tok->r_count].arg = ft_strdup(arg);
    else
        tok->r[tok->r_count].arg = strip_quotes(arg);
    tok->r_count++;
}

