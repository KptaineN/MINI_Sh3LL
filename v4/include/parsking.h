
#ifndef PARSKING_H
# define PARSKING_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

/* =========================
 * STRUCTURES
 * ========================= */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_arr
{
	void			**arr;
	int				len;
}	t_arr;

typedef struct s_dic
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
}	t_toktype;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef struct s_subtoken
{
	t_quote_type	type;
	char			*p;
	int				len;
}	t_subtoken;

typedef struct s_subtoken_container
{
	t_subtoken		*parts;
	int				n_parts;
}	t_subtoken_container;

typedef struct s_token
{
	char					type;
	char					*value;
	t_subtoken_container	*cmd_args_parts;
	struct s_token			*next;
}	t_token;

typedef struct s_shell
{
    char            *input;        // ligne de commande brute
    char            **args;        // arguments courants de la commande
    t_arr           *parsed_args;  // tableau de tokens bruts
    int             n_tokens;      // nombre total de tokens
    int             n_cmd;         // nombre de commandes
    t_token         *tokens;       // tableau de tokens
    t_list          *cmd_tail;     // liste chainée des commandes
    t_list          *cmd_head;     // tête de liste
    t_list          *env;          // environnement (liste chaînée)
    int             fd_in;         // entrée redirection
    int             fd_out;        // sortie redirection
    t_arr           *bcmd;         // builtins
    t_arr           *oper;         // opérateurs
    pid_t           *pids;         // pids des process enfants
    int             fd_pid[2];     // pipe pour PIDs
    t_subtoken_container *heredoc; // gestion heredoc
    int             exit_status;   // dernier code de sortie
}   t_shell;


/* =========================
 * PROTOTYPES
 * ========================= */

/* --- Utils --- */
bool    escape_check(const char *str, int idx);
size_t  t_arrlen(void **arr);
int     is_in_t_arr_str(t_arr *arr, const char *arg);
int     is_in_t_arr_dic_str(t_arr *arr, const char *arg);
void    build_t_arr_str(t_arr **dst, char **arr_str, int len);
void    init_all_t_arr(t_shell *shell);

/* --- Parsing & Tokens --- */
t_arr   *custom_split(const char *str, t_shell *shell);
int     count_tokens(t_shell *shell, t_arr *parsed_args, t_arr *oper);
void    attribute_token_type(t_shell *shell);
int     count_args_cmd(t_shell *shell, int i);
int     attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len);
int     count_subtokens(const char *str);
void    subtoken_of_cmd(t_subtoken_container *container, char *arg);
int     find_c_nonescaped(const char *str, char *needle, int size_needle);

/* --- Redirections --- */
void    file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i);

/* --- t_list utils --- */
t_list  *ft_lstnew(void *content);
void    ft_lstadd_back(t_list **lst, t_list *new);
void    ft_lstadd_front(t_list **lst, void *content);
t_list  *search_lst(t_list *lst, const char *target);
void    replace_or_add_env(t_list **env, const char *key, const char *value);
void    free_env_list(t_list *env);

/* --- t_arr utils --- */
int     is_in_t_arr_dic_str(t_arr *arr, const char *arg);

/* --- Display --- */
void    print_all_parts(t_shell *shell);
void    print_dic(t_arr *arr);

#endif // PARSKING_H
