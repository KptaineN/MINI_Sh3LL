/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:45:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/06/17 15:00:28 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "LIBFT/libft.h"
# include "ast.h"
# include "env.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_minishell
{
	char **args; // Arguments de la commande courante
	char *input; // Ligne utilisateur brute
	int	exit_status;
	t_ast *ast; // Arbre syntaxique abstrait (AST)
	t_env *env; // Liste chainée de l'environnement
}		t_minishell;

// Fonctions globales d'initialisation
int		start_minishell(t_minishell *shell, char **envp);
void	init_minishell(t_minishell *shell, char **envp);
//int		main_loop(t_minishell *shell);
int	looping(t_minishell *shell);

void	free_minishell(t_minishell *shell);

// Gestion du prompt et boucle utilisateur
void	print_prompt(t_minishell *shell);
//void	parse_input(t_minishell *shell);
void	execute_command(t_minishell *shell);

// parser
void	parse_input(t_minishell *shell);

// Divers utilitaires
void	handle_error(const char *message);

//void	parse_input(t_minishell *shell);
// Function prototypes

void	handle_signal(int signal);
void	print_prompt(t_minishell *shell);
void	handle_cd(t_minishell *shell);
void	handle_exit(t_minishell *shell);
void	handle_env(t_minishell *shell);
void	handle_export(t_minishell *shell);
void	handle_unset(t_minishell *shell);
void	handle_echo(t_minishell *shell);
void	handle_pipes(t_minishell *shell);
void	handle_redirection(t_minishell *shell);
void	handle_builtin(t_minishell *shell);
void	handle_external(t_minishell *shell);
void	handle_error(const char *message);
void	free_ast(t_ast *ast);
void	execute_ast(t_ast *ast, t_env *env);
void	execute_ast_pipeline(t_ast *ast, t_env *env, int input_fd);

int is_builtin(const char *cmd);
//int		is_builtin(t_ast *ast);
int execute_builtin(t_ast *cmd, t_env *env);
//void	execute_builtin(t_minishell *shell, t_ast *ast);


void	execute_simple(t_ast *ast, t_env *env);
// void    execute_command(t_ast *ast, t_env *env);
void	execute_pipeline(t_ast *ast, t_env *env);
void	execute_simple_command(t_ast *ast, t_env *env);
void	setup_redirections(t_ast *ast);
void	exec_cmd_node(t_ast *ast, t_env *env, int input_fd);
void	exec_pipe_node(t_ast *ast, t_env *env, int input_fd);
// void    first_child(t_pipex *pipex, t_exec *exec, char *cmd);
// void    second_child(t_pipex *pipex, t_exec *exec, char *cmd);
// void    child_process(t_pipex *pipex, t_exec *exec, t_child *child_data);
void	initialize_positions_forsplitdemesc(int pos[3]);

void	ft_free_array(char **array);
//void	ft_free_split(char **ft_split);
char	*get_env_value(t_env *env, const char *name);
//char	*find_cmd(char *cmd, t_env *env);
char	*ft_strjoin_3(const char *a, const char *b, const char *c);
char	*get_valid_path(char *cmd, t_env *envp);
char	*search_in_paths(char **paths, char *cmd);
char	*find_command_path(char *cmd, t_env *env);
char	*get_env_value(t_env *env, const char *name);
//char	*ft_strjoin_3(const char *a, const char *b, const char *c);
//char	*find_cmd(char *cmd, t_env *env);
void	ft_free_split(char **tab);

int	is_pipeline(t_ast *ast);

//...
char	**env_to_envp(t_env *env);
//...
void	handle_error(const char *message);

//signal.c
void	init_signals(void);
//

//from_pipex de me c
char *get_env_path(char **envp, const char *name);
char *join_with_slash(const char *prefix, const char *suffix);
char	*pwd_path(char *cmd, t_env *env);

//
char *find_cmd(const char *cmd, t_env *env);

//char **split_on_pipes(const char *input);
t_ast *parse_redirection(char **args);
void free_strtab(char **tab);

//
void print_ast(t_ast *node, int level);
//

#endif // MINISHELL_H

// ************************************************************************** */
