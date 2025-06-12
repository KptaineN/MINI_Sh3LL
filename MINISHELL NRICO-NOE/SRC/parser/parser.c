#include "../../include/minishell.h"

void parse_input(t_minishell *shell)
{
    // Exemples : découpe sur les pipes (à améliorer ensuite)
    // ["ls -l", "grep .c"]
    shell->ast = parse_line_to_ast(shell->input);
}
