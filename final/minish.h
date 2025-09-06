/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>


/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

extern sig_atomic_t			g_exit_status;

typedef struct s_launch		t_launch;
typedef struct s_sh			t_sh;
typedef struct s_list		t_list;
typedef struct s_arr		t_arr;
typedef struct s_env		t_env;
typedef struct s_dic		t_dic;
typedef enum e_quote_state	t_quote_state;

// Generic linked list structure
typedef struct s_list
{
	void					*content;
	void					**arr_content;
	struct s_list			*next;
}							t_list;

typedef struct s_env
{
	char					*key;
	char					*value;
}							t_env;

typedef struct s_arr // array de string
{
	void **arr;
	int len;
}							t_arr;

// Quote states for parsing
typedef enum e_quote_state
{
	QUOTE_NONE,   // Outside quotes
	QUOTE_SINGLE, // Inside single quotes ''
	QUOTE_DOUBLE  // Inside double quotes ""
}							t_quote_state;

typedef struct s_dic // array de string
{
	void *key;
	void *value;
}							t_dic;

typedef void				(*t_family)(t_sh *, t_list *, t_launch *);

typedef struct s_launch
{
	int						*pids;
	int						prev_pipe[2];
	int						curr_pipe[2];
	int						fd_pid[2];
	int						*pid;
	int						*idx;
}							t_launch;

typedef struct s_sh
{
	char					*input;
	int						n_parsed;
	char **args;        //
	char **parsed_args; //	premier parsing pere
	t_list					*cmd;
	//	disperse les cmd_line aux enfants (le arr_content avec leur partie)
	int						n_cmd;
	//  puis expansion de la part de l'enfant et repartit les pipes et les WORD
	//  cree la arr_string de la cmd finale
	t_list					*env;
	int						fd_in;
	int						fd_out;
	t_arr					*bcmd;
	t_arr					*oper;
	pid_t					*pids;
	int						fd_pid[2];
	char					**exec_envp_tmp;
	char					*exec_cmd_path_tmp;
	t_list					*exec_candidates_tmp;
	t_family				**f_core;
	int						*pipe_to_close[2];
}							t_sh;


//								SIDE STRUCTURES                                     //
typedef struct s_build_cmd
{
	int i;
	int j;
	t_list *head;
	t_list *curr;
}	t_build_cmd;
//////////////////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/*                           FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

// start_sh
void						init_sh(t_sh *sh, char **envp);

// process_input
int							looping(t_sh *sh);

// free enrico
void						free_string_array(char **arr);
void						free_t_arr_dic(t_arr **arr);
void						free_sh(t_sh *sh);
void						free_t_list(t_list **env_list);

char						*find_command_path(char *cmd, t_list *env);

// split
bool 						escape_check(char *in, int idx);
char 						**custom_split(char *in);

// signal
void						signal_reset_prompt(int signo);
void						set_signals_interactive(void);
void						signal_print_newline(int signal);
void						set_signals_noninteractive(void);
void						ignore_sigquit(void);

// PATH
t_list						*ft_lstnew(void *content);
t_list						*set_linked_env(char **env);
void						push_lst(t_list **tail, void *content);
void						advance_node(t_list **node);
char						*find_command_path(char *cmd, t_list *env);
int							set_env_value(t_list **env, const char *key,
								const char *value);

// expansion
int							count_escape_char_before(const char *str, int idx);
int							handle_escape_count(const char *str, int *i,
								int len);
char						*handle_escape_write(char *dst, const char *src,
								int *i, int *j);
char						*expand_single_string(char *str, t_list *env_list);
char						*get_env_value(t_list *env_list, const char *key);
//


//							BUILD_CMD.C												//
t_list						*build_cmd(t_sh *sh, char **parsed);
void						parse_and_prepare(t_sh *sh, char *in);
//////////////////////////////////////////////////////////////////////////////////////

// child
void						**pid_expansion(void **v_arr, t_list *env);
void						one_child(t_sh *sh, t_list *cmd, t_launch *all);
void						multi_child(t_sh *sh, t_list *cmd, t_launch *all);
void						end_child(t_sh *sh, t_list *cmd, t_launch *all);

// parent
void						one_parent(t_sh *sh, t_list *cmd, t_launch *all);
void						multi_parent(t_sh *sh, t_list *cmd, t_launch *all);
void						end_parent(t_sh *sh, t_list *cmd, t_launch *all);

// launch
void						execution_button(char **cmd_line, t_sh *sh);
void						launch_process(t_sh *sh);

void						replace_or_add(t_list **lst, const char *old,
								const char *new);
void						add_env(t_sh *sh, const char *key, int fd);
void						send_pid(int fd, int pid);

char						**expansion_partition_redirection(t_list *cmd,
								t_list *env, t_arr *oper);
/*
** VARIABLE EXPANSION FUNCTIONS
** Handle $VAR and ${VAR} expansion with quote and escape support
*/
char						**expand_variables(char **input_array,
								t_list *env_list);

/*
** ENVIRONMENT MANIPULATION FUNCTIONS
** Add, remove, and retrieve environment variables
*/
int							env_set_var(t_list **env_list, const char *key,
								const char *value);
int							env_unset_var(t_list **env_list, const char *key);
char						*env_get_var(t_list *env_list, const char *key);

/*
** MEMORY MANAGEMENT FUNCTIONS
** Clean up allocated memory for arrays and lists
*/
void						free_string_array(char **array);
void						free_env_list(t_list **env_list);
void						free_linked_list_of_array_string(t_list *head);

/*
** UTILITY/DEBUG FUNCTIONS
** Helper functions for testing and debugging
*/
void						print_env_list(t_list *env_list);
void						test_quote_expansion(t_list *env_list);
void						example_env_usage(char **envp);

/*
** LIBFT FUNCTIONS REQUIRED
** These must be implemented in your libft
*/
size_t						ft_strlen(const char *s);
char						*ft_strdup(const char *s1);
char						*ft_strndup(const char *s1, size_t n);
int							ft_strcmp(const char *s1, const char *s2);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strcpy(char *dst, const char *src);
void						*ft_calloc(size_t count, size_t size);
void						ft_bzero(void *s, size_t n);
int							ft_isalnum(int c);
char						*ft_strncpy(char *dest, const char *src, size_t n);
char						*ft_strchr(const char *s, int c);
void						*ft_memcpy(void *dst, const char *src, size_t n);
void						*ft_memset(void *s, int c, size_t len);
void						ft_putstr_fd(char *s, int fd);
char						*ft_itoa(int n);
char						*ft_substr(const char *s, unsigned int start,
								size_t len);
int							ft_isdigit(int c);
int							ft_atoi(const char *str);
void						ft_putchar_fd(char c, int fd);
int							ft_isalpha(int c);
void						ft_putendl_fd(const char *s, int fd);
int							count_digits(long n);
char						*ft_itoa_inplace(char *buf, int n);

// functions

/* --- Builtins (parser) --- */
int							builtin_echo(void *v_sh, void **v_argv);
int							builtin_cd(void *v_sh, void **v_argv);
int							builtin_export(void *v_sh, void **v_argv);
int							builtin_env(void *v_sh, void **v_argv);
int							builtin_exit(void *v_sh, void **v_argv);
int							builtin_pwd(void *v_sh, void **v_argv);
int							builtin_unset(void *v_sh, void **v_argv);

// redir
int							handle_heredoc(void *v_file, void **v_arr, int *fd);
int							input_redirection(void *v_file, void **v_arr,
								int *fd);
int							output_redirection(void *v_file, void **v_arr,
								int *fd);
int							append_redirection(void *v_file, void **v_arr,
								int *fd);

int							is_in_t_arr_str(t_arr *arr, const char *arg);
int							is_in_t_arr_dic_str(t_arr *arr, const char *arg);
void						build_t_arr_str(t_arr **dst, char **arr_str,
								int len);
void						init_all_t_arr(t_sh *sh);

// Function to display the linked list of string arrays
void						display_linked_list_of_string_array(t_list *head);
void						display_string_array(char *arr[]);
void						display_linked_list_of_string(t_list *head);

#endif