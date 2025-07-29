/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:45:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/07/28 14:26:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define _POSIX_C_SOURCE 200809L

#include "LIBFT/libft.h"
#include "env.h"
#include "parsking.h"
#include "../SRC/built/echo/echo.h"
#include "../SRC/built/export/export.h"

#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_shell  t_shell;
typedef struct s_env    t_env;

typedef struct s_minishell
{
	t_shell  parser;
	//t_env   *env;
	char   **args;
	//char    *input;
	int      exit_status;
} t_minishell;

/* Initialization and cleanup */
int  start_minishell(t_minishell *shell, char **envp);
void init_minishell(t_minishell *shell, char **envp);
int  looping(t_minishell *shell);
void free_minishell(t_minishell *shell);
void free_tokens(t_shell *parser);
/* Prompt and execution */
void print_prompt(t_minishell *shell);
void execute_command(t_minishell *shell);

/* Builtins */
int builtin_cd(char **args, t_minishell *shell);
int builtin_pwd(void);
int builtin_echo(t_minishell *shell, t_token *token);
int builtin_env(char **args, t_minishell *shell);
int builtin_export(t_token *token, t_minishell *shell);

//int builtin_export(char **args, t_minishell *shell);
int builtin_unset(char **args, t_minishell *shell);
int builtin_exit(t_minishell *shell, t_token *token);
void exit_shell(t_minishell *shell, int exit_code); // ← ajoute ça ici
/* Utilities */
char *ft_strjoin3(char *a, const char *b, const char *c, int free_a);
char *get_env_value(t_env *env, const char *name);
char *find_cmd(const char *cmd, t_env *env);
char *get_valid_path(char *cmd, t_env *env);
char *search_in_paths(char **paths, char *cmd);
char **env_to_envp(t_env *env);
int    env_len(t_env *env);
char *replace_exit_code(const char *input, int exit_code);
char *replace_variables(const char *arg, t_minishell *shell);
char *expand_argument(const char *arg, t_minishell *shell);
int    count_args(char **args);
void free_tab(char **tab);

void handle_error(const char *message);
void init_signals(void);

void handle_cd(t_minishell *shell);
void handle_exit(t_minishell *shell);
void handle_env(t_minishell *shell);
void handle_export(t_minishell *shell);
void handle_unset(t_minishell *shell);
void handle_echo(t_minishell *shell);
int is_builtin(const char *cmd);
void free_parser(t_shell *parser);
void handle_heredoc(t_minishell *shell, int token_idx);
void handle_append(t_minishell *shell, int token_idx);
void handle_and(t_minishell *shell, int token_idx);
void handle_or(t_minishell *shell, int token_idx);
void handle_pipe(t_minishell *shell, int token_idx);
void handle_redirect_in(t_minishell *shell, int token_idx);
void handle_redirect_out(t_minishell *shell, int token_idx);
void ft_free(void **thing);


#endif // MINISHELL_H
