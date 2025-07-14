/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:38:32 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/14 18:01:47 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsking.h"
#include "../../include/minishell.h"

int ft_echo(void *sh, int token_idx)
{
    t_minishell *shell = (t_minishell *)sh;
    t_token    *tok   = &shell->parser.tokens[token_idx];

    return builtin_echo(shell, tok);
}

int ft_cd(void *shell, int token_idx)
{
    t_minishell *sh  = (t_minishell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    char        **args = reconstruct_args(tok->u.cmd_args_parts);

    return builtin_cd(args, sh);
}

int ft_pwd(void *shell, int token_idx)
{
    (void)shell;
    (void)token_idx;
    return builtin_pwd();
}

int ft_export(void *shell, int token_idx)
{
    t_minishell *sh  = (t_minishell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
   //char        **args = reconstruct_args(tok->u.cmd_args_parts);

    return builtin_export(tok, sh);
}

int ft_unset(void *shell, int token_idx)
{
    t_minishell *sh  = (t_minishell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    char        **args = reconstruct_args(tok->u.cmd_args_parts);

    return builtin_unset(args, sh);
}

int ft_env(void *shell, int token_idx)
{
    t_minishell *sh  = (t_minishell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    char        **args = reconstruct_args(tok->u.cmd_args_parts);

    return builtin_env(args, sh);
}

int ft_exit(void *shell, int token_idx)
{
    t_minishell *sh  = (t_minishell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];

    return builtin_exit(sh, tok);
}
