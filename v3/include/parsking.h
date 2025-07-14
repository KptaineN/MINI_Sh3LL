
#ifndef MINI_H
# define MINI_H

// Forward declarations
typedef struct s_minishell t_minishell;
typedef struct s_env t_env;
# include <stdio.h>             // printf, perror, etc.

# include <dirent.h>            // opendir, readdir (for wildcard expansion)
# include <errno.h>             // errno, error handling
# include <fcntl.h>             // open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC,
# include <readline/history.h>  // History functionality
# include <readline/readline.h> // GNU Readline (if allowed in your project)
# include <signal.h>            // signal handling (Ctrl+C, etc.)
# include <stdbool.h>           // opendir, readdir (for wildcard expansion)

# include <stdlib.h>            // malloc, free, exit, getenv, setenv
# include <string.h>            // strcmp, strlen, strcpy, strdup, strtok
# include <sys/ioctl.h>         // Terminal size, ioctl calls
# include <sys/stat.h>          // stat, access (for checking file existence)
# include <sys/types.h>         // pid_t, size_t (often included by others)
# include <sys/wait.h>          // wait, waitpid, WIFEXITED, WEXITSTATUS
# include <termios.h>           // Terminal control (if doing line editing)
# include <unistd.h>            // fork, execve, pipe, dup, dup2, close, chdir,


// environment
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_arr //array de string
{
	void			**arr;
	int				len;
}					t_arr;

typedef struct s_dic //array de string
{
	void *key;
	void *value;
}	t_dic;

typedef enum e_toktype
{
	TOKEN_WORD,
	TOKEN_BCMD,
	TOKEN_CMD,
	TOKEN_OPER
}					t_toktype;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}					t_quote_type;

// for quoted unquoted and double quoted
typedef struct s_subtoken
{
	t_quote_type	type;
	char			*p; // pointer
	int 			len; // size
}					t_subtoken;

typedef struct s_subtoken_container

{
	t_subtoken		*parts;		// "\"hamman\"asd\'Papa\'"
	    int count;          // nombre de sous-tokens
	int				n_parts;
}      t_subtoken_container;


// tokens
typedef struct s_token
{
	int idx; // position du token dans shell->tokens
	char			type;
	char			*value; 	// if command, then here is the path
	union	u_sub 
	{
		int         			(*oper_handlers)(void *, int);	//operator
		t_subtoken_container	all_parts;						//word
		t_subtoken_container	*cmd_args_parts;				//cmd
	} u;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			*input;
	t_arr			*parsed_args;
	int				n_tokens;
	int 			n_cmd;
	t_token			*tokens;
	t_list			*cmd_tail;
	t_list			*cmd_head;
	t_list			*env;
	int				smaller;	// <
	int				bigger;		// >
	int				append;		// >>
	int				doc;		// here doc
	int				fd_in;
	int				fd_out;
	//t_cmd			*tree;
	t_arr			*bcmd;
	t_arr			*oper;
	//int             (**oper_handlers)(void *, int);		//voir init_oper_handlers
}					t_shell;

//t_list
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*set_linked_path(char **env);
char **linked_to_array_string(t_list *node);
int execute_builtin(t_minishell *shell, int token_idx);
int count_subtoken_args(t_subtoken_container *args);
//t_arr
size_t t_arrlen(void **arr);
int is_in_t_arr_str(t_arr *arr, const char *arg);
int is_in_t_arr_dic_str(t_arr *arr, const char *arg);
void build_t_arr_str(t_arr **dst, char **arr_str, int len);
void init_all_t_arr(t_shell *shell);

//path
char *find_command_path(char *cmd, t_list *env);

//costum split
char *ft_strdup(const char *s1); // get rid later
bool escape_check(const char *str ,int idx);
t_arr 	*custom_split(const char *str, t_shell * shell);

//lexer tools
int find_c_nonescaped(const char *str, char *needle, int size_needle);
int count_subtokens(const char *str);
int count_tokens(t_shell *shell);

//lexer
void attribute_subtoken_type(t_token *token);
void attribute_token_type(t_shell *shell);

//builtin
char **reconstruct_args(t_subtoken_container *args);
int execute_builtin(t_minishell *shell, int i);

//launch
//int start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd);
//int end_cmd(t_shell *shell,int *prev_pipe, t_list *curr_cmd);
//void launch_process(t_shell *shell);
//oid one_command(t_shell *shell);

//cmd
bool is_command(char *str, t_list *env);

// oper handlers function
int handle_heredoc(void *shell, int token_idx);
int handle_append(void *shell, int token_idx);
int handle_and(void *shell, int token_idx);
int handle_or(void *shell, int token_idx);
int handle_pipe(void *shell, int token_idx);
int handle_redirect_in(void *shell, int token_idx);
int handle_redirect_out(void *shell, int token_idx);

// builtin func
int ft_export(void *shell, int token_idx);
int ft_unset(void *shell, int token_idx);
int ft_exit(void *shell, int token_idx);
int ft_env(void *shell, int token_idx);
int ft_pwd(void *shell, int token_idx);
int ft_echo(void *shell, int token_idx);
int ft_cd(void *shell, int token_idx);

char *join_subtokens(t_subtoken_container container);


//display
void print_all_parts(t_shell *shell);
void	print_dic(t_arr *arr);

// Ancienne déclaration (incorrecte maintenant)
//void one_command(t_shell *shell);
//void launch_process(t_shell *shell);

// Nouvelle version correcte :
void one_command(t_minishell *shell);
void launch_process(t_minishell *shell);
void execute_cmd(t_minishell *shell, t_list *curr_cmd);
int start_cmd(t_minishell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd);
int end_cmd(t_minishell *shell, int *prev_pipe, t_list *curr_cmd);

char *join_subtokens(t_subtoken_container container);

#endif
