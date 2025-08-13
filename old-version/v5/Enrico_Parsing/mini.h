
#ifndef MINI_H
# define MINI_H

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
	t_quote_type	type; //double, single, unquote
	char			*p; // pointer
	int 			len; // size
}					t_subtoken;

typedef struct s_subtoken_conainter
{
	t_subtoken		*parts;		// "\"hamman\"asd\'Papa\'" -> "hamman", asd, ’Papa’ 
	int				n_parts;	// 3
}	t_subtoken_conainter;

// tokens
typedef struct s_token
{
	char			type; // command 
	char			*value; 	// echo "\"hamman\"asd\'Papa\'"
	t_subtoken_conainter	*cmd_args_parts;	// array {echo, \"hamman\"asd\'Papa\'}
	int n_parts;	// 2
}					t_token;

typedef struct s_shell
{
	t_arr			*parsed_args;
	int				n_tokens;
	int 			n_cmd;
	t_token			*tokens;		// array de token
	t_list			*cmd_tail;		//type: t_token, dernier pour iterer  
	t_list			*cmd_head;		//type: t_token, liste chainé des , premier
	t_list			*env;
	int				fd_in;
	int				fd_out;
	//t_cmd			*tree;
	
	// REGARDE t_arr, array de pointer + len
	t_arr			*bcmd;		// type: array de type dic            
	t_arr			*oper;		// type: array de type dic
	pid_t			*pids;		//array de pids
}					t_shell;

//str_utils
char *ft_strdup_count(const char *s, int *count);
//void ft_swap(void *a, void *b);
char *ft_itoa_inplace(char *s, int n);

//t_list
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstadd_front(t_list **lst, void *content);
t_list	*set_linked_path(char **env);
char **linked_to_array_string(t_list *node);
void	push_lst(t_list **tail, void *content);
t_list *search_lst(t_list *lst, const char *target);
void replace_or_add(t_list **lst, const char *old, const char *new);

//t_arr
size_t t_arrlen(void **arr);
int is_in_t_arr_str(t_arr *arr, const char *arg);
int is_in_t_arr_dic_str(t_arr *arr, const char *arg);
void build_t_arr_str(t_arr **dst, char **arr_str, int len);
void init_all_t_arr(t_shell *shell);

//path
char *find_command_path(char *cmd, t_list *env);
char **expand_cmd(t_token *token, t_list *env);
char	*get_value_env(t_list *env, char *value, int len);
void execute(t_shell *shell, t_token *cmd);

//costum split
char *ft_strdup(const char *s1); // get rid later
bool escape_check(const char *str ,int idx);
t_arr 	*custom_split(const char *str, t_shell * shell);

//operator
void file_access_redirection(t_shell *shell, int t_arr_index, int i);
void handle_heredoc(t_shell *shell, int i);

//lexer tools
int find_c_nonescaped(const char *str, char *needle, int size_needle);
int count_subtokens(const char *str);
int count_tokens(t_shell *shell);

//lexer
void attribute_subtoken_type(t_token *token);
void attribute_token_type(t_shell *shell);

//launch
int start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe);
int end_cmd(t_shell *shell,int *prev_pipe);
void launch_process(t_shell *shell);
void one_command(t_shell *shell);

//cmd
bool is_command(char *str, t_list *env);

// builtin func
int ft_export(void *shell, int token_idx);
int ft_unset(void *shell, int token_idx);
int ft_exit(void *shell, int token_idx);
int ft_env(void *shell, int token_idx);
int ft_pwd(void *shell, int token_idx);
int ft_echo(void *shell, int token_idx);
int ft_cd(void *shell, int token_idx);


//display
void print_all_parts(t_shell *shell);
void	print_dic(t_arr *arr);
void printStringArray(const char *cmd, const char *arr[]);

//free_section
void ft_free(void **thing);


#endif
