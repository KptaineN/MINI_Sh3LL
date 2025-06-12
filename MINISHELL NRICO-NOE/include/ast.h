#ifndef AST_H
# define AST_H

#include "minishell.h"

typedef enum e_node_type
{
    NODE_COMMAND,       // une commande simple
    NODE_PIPE,          // un pipe "|"
    NODE_REDIR_IN,      // une redirection input "<"
    NODE_REDIR_OUT,     // une redirection output ">"
    NODE_AND,          // une commande AND "&&"
    NODE_OR,           // une commande OR "||"
    NODE_REDIR_APPEND,  // une redirection output ">>"
    NODE_HEREDOC        // une redirection heredoc "<<"
}   t_node_type;

// Un nœud d'AST : il peut représenter une commande, un pipe, une redirection...
typedef struct s_ast
{
    t_node_type     type;
    char            **args;
    char            *filename;
    struct s_ast    *left;
    struct s_ast    *right;
}   t_ast;

// Fonctions de gestion de l'AST
void    free_ast(t_ast *ast);

// ... autres prototypes liés à l'AST

#endif
