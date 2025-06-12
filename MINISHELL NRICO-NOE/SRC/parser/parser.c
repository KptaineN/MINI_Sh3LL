#include "../../include/minishell.h"

//test
t_ast *parse_line_to_ast(const char *input)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = NODE_COMMAND;
    node->args = ft_split(input, ' '); // Pas gestion des quotes ni pipes ici, juste split simple
    node->filename = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void parse_input(t_minishell *shell)
{
    // Exemples : découpe sur les pipes (à améliorer ensuite)
    // ["ls -l", "grep .c"]
    shell->ast = parse_line_to_ast(shell->input);
}
