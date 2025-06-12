/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:45:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/12 11:25:07 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "LIBFT/libft.h"
#include "ast.h"
#include "env.h"


typedef struct s_minishell
{
    char **envp; // Environment variables
    char **args; // Command arguments
    char *input; // User input
    int exit_status; // Exit status of the last command
    t_ast *ast; // Abstract Syntax Tree for command parsing
    t_env *env; // Linked list of environment variables

} t_minishell;

void    parse_input(t_minishell *shell);
// Function prototypes
int     start_init_minishell(t_minishell *shell, char **envp);
void    init_minishell(t_minishell *shell, char **envp);
void    free_minishell(t_minishell *shell);
void    execute_command(t_minishell *shell);
void    handle_signal(int signal);
void    print_prompt(t_minishell *shell);
void    handle_cd(t_minishell *shell);
void    handle_exit(t_minishell *shell);
void    handle_env(t_minishell *shell);
void    handle_export(t_minishell *shell);
void    handle_unset(t_minishell *shell);
void    handle_echo(t_minishell *shell);
void    handle_pipes(t_minishell *shell);
void    handle_redirection(t_minishell *shell);
void    handle_builtin(t_minishell *shell);
void    handle_external(t_minishell *shell);
void    handle_error(const char *message);




#endif
