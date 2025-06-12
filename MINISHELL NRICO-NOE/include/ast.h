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
    t_node_type     type;       // type du nœud, d’action représentée (commande, pipe, etc)
    char            **args;     // arguments de la commande (ou NULL si pas une commande)
    int             append;      // descripteur de fichier pour redirection input (sinon -1)
    char            *filename;  // nom du fichier pour une redirection (sinon NULL)
    struct s_ast    *left;      // branche gauche (ex: commande avant un pipe)
    struct s_ast    *right;     // branche droite (ex: commande après un pipe)
}   t_ast;

#endif
