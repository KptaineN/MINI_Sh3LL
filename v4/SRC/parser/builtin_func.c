/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:38:32 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:28:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsking.h"
#include "../../include/minishell.h"

int ft_echo(void *sh, int token_idx)
{
    t_shell *shell = (t_shell *)sh;
    t_token    *tok   = &shell->parser.tokens[token_idx];
    (void)token_idx;
    (void)tok; // Suppress unused variable warning
    return builtin_echo(shell, tok);
}

int ft_cd(void *shell, int token_idx)
{
    t_shell *sh  = (t_shell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    //char        **args = reconstruct_args(tok->cmd_args_parts);
    (void)token_idx;
    char        **args = NULL;
    (void)tok; // Suppress unused variable warning
    (void)args; // Suppress unused variable warning
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
    t_shell *sh  = (t_shell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
   //char        **args = reconstruct_args(tok->u.cmd_args_parts);
    (void)token_idx;
   char        **args = NULL;
    (void)args; // Suppress unused variable warning

   (void)tok; // Suppress unused variable warning
    return builtin_export(tok, sh);
}

int ft_unset(void *shell, int token_idx)
{
    t_shell *sh  = (t_shell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
   // char        **args = reconstruct_args(tok->cmd_args_parts);
   (void)token_idx; 
   char        **args = NULL;
    (void)tok; // Suppress unused variable warning
    return builtin_unset(args, sh);
}

int ft_env(void *shell, int token_idx)
{
    t_shell *sh  = (t_shell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    //char        **args = reconstruct_args(tok->cmd_args_parts);
    (void)token_idx;
    char        **args = NULL;
    (void)tok; // Suppress unused variable warning
    return builtin_env(args, sh);
}

int ft_exit(void *shell, int token_idx)
{
    t_shell *sh  = (t_shell *)shell;
    t_token     *tok = &sh->parser.tokens[token_idx];
    (void)token_idx;
    (void)tok; // Suppress unused variable warning
    return builtin_exit(sh, tok);
}
