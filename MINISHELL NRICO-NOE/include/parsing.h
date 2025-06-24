#ifndef PARSING_H
# define PARSING_H

#include "minishell.h" // Include the main header for the shell

typedef struct s_minishell t_minishell;

// Libraries and headers
/* ************************************************************************** *
# include <stdio.h>             // printf, perror, etc.

# include <dirent.h>            // opendir, readdir (for wildcard expansion)
# include <errno.h>             // errno, error handling
# include <fcntl.h>             // open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC,
# include <readline/history.h>  // History functionality
# include <readline/readline.h> // GNU Readline (if allowed in your project)
# include <signal.h>            // signal handling (Ctrl+C, etc.)
        // opendir, readdir (for wildcard expansion)

# include <stdlib.h>            // malloc, free, exit, getenv, setenv
# include <string.h>            // strcmp, strlen, strcpy, strdup, strtok
# include <sys/ioctl.h>         // Terminal size, ioctl calls
# include <sys/stat.h>          // stat, access (for checking file existence)
# include <sys/types.h>         // pid_t, size_t (often included by others)
# include <sys/wait.h>          // wait, waitpid, WIFEXITED, WEXITSTATUS
# include <termios.h>           // Terminal control (if doing line editing)
# include <unistd.h>            // fork, execve, pipe, dup, dup2, close, chdir,
***************************************************************************** */
# include <stdbool.h>   
// environment
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_arr
{
	char			**arr;
	int				len;
}					t_arr;

typedef enum e_toktype
{
	TOKEN_WORD,
	TOKEN_BCMD,
	TOKEN_CMD,
	TOKEN_OPER,
	TOKEN_UNKNOWN
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
	char *p; // pointer
	int len; // size
}					t_subtoken;

typedef struct s_subtoken_conainter
{
	t_subtoken	*parts;
	int				n_parts;
}	t_subtoken_conainter;

// tokens
typedef struct s_token
{
	char			type;
	char			*value;
	union	u_sub 
	{
		t_arr					**cmd_args;
		int         			(*oper_handlers)(void *, int);	//operator
		t_subtoken_conainter	all_parts;							//word
	} u;
}					t_token;

typedef struct s_shell
{
	char			*input;
	t_arr			*parsed_args;
	int				token_count;
	t_token			*tokens;
	t_list			*env;
	//t_cmd			*tree;
	t_arr			*bcmd;
	t_arr			*oper;
	int             (**oper_handlers)(void *, int);		//voir init_oper_handlers
}					t_shell;

/* découpage et tokenisation */
int     count_tokens(const char *str);
int     count_subtoken(const char *str);
char    *find_c_needle(const char *str, char *needle, int size_needle);
void    attribute_subtoken_type(t_token *token);
char    *extract_token(const char *str, int *start);
t_arr   *custom_split(const char *str);

/* détection de type */
int     is_in_t_arr(t_arr *arr, char *arg);
bool    is_command(char *str);
void    attribute_token_type(t_shell *shell);

/* init opérateurs + builtins */
void    init_operator_handlers(t_shell *shell);
void    init_all_t_arr(t_shell *shell);

/* affichage debug */
void    print_all_parts(t_shell *shell);

// oper handlers function
int handle_heredoc(void *shell, int token_idx);
int handle_append(void *shell, int token_idx);
int handle_and(void *shell, int token_idx);
int handle_or(void *shell, int token_idx);
int handle_pipe(void *shell, int token_idx);
int handle_redirect_in(void *shell, int token_idx);
int handle_redirect_out(void *shell, int token_idx);

void    build_t_arr(t_arr **dst, char **arr_str, int len);
size_t  ft_arrlen(char **arr);
//void    parse_input(t_minishell *shell);
t_ast   *init_redirection_node(t_node_type type, const char *filename, t_ast *child);
void    parse_input(t_minishell *shell);

#endif