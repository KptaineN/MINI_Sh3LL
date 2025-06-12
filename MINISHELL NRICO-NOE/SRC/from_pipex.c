#include "../include/minishell.h"

int is_pipeline(t_ast *ast)
{
    if (!ast)
        return (0);
    // Si la racine est un pipe
    if (ast->type == NODE_PIPE)
        return (1);
    // Si la racine est une redirection dont le left est un pipe
    if ((ast->type == NODE_REDIR_OUT || ast->type == NODE_REDIR_IN
        || ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
        && ast->left && ast->left->type == NODE_PIPE)
        return (1);
    return (0);
}
