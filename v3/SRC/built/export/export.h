#ifndef EXPORT_H
#define EXPORT_H

#include "../../../include/minishell.h"
#include "../../../include/parsking.h"

// Au début de ton header (ex : echo.h ou export.h)

#include "../../include/struct.h"


int builtin_export(t_token *token, t_minishell *shell);

int export_no_arguments(t_minishell *shell);
int process_export_argument(char *arg, t_minishell *shell);
// --- export_utils.c ---
size_t env_count(t_minishell *shell);
char **env_to_array(t_minishell *shell);
void print_export_arr(char **arr);
void free_export_arr(char **arr);
int export_no_arguments(t_minishell *shell);

// --- export_args.c ---
int is_valid_identifier(const char *name);
int handle_arg_with_assignment(char *arg, t_minishell *shell);
int handle_arg_without_assignment(char *arg, t_minishell *shell);
int process_export_argument(char *arg, t_minishell *shell);

// --- export_env.c ---
t_list *find_env_var(t_minishell *shell, const char *key);
int update_env_var(t_list *env, const char *value);
int create_env_var(t_minishell *shell, const char *key, const char *value);
int set_env_var(t_minishell *shell, const char *key, const char *value);
char *create_env_entry(char *env_line);

#endif
