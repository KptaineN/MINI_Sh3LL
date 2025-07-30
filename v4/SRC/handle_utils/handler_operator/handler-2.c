#include "../../../include/minishell.h"


void handle_pipe(t_shell *shell, int token_idx)
{
    (void) shell;
    printf("Handling PIPE (|) at token %d\n", token_idx);
    // TODO: Implement pipe logic
    
}
void handle_redirect_in(t_shell *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_IN (<) at token %d\n", token_idx);
    // TODO: Implement input redirection logic
    
}
void handle_redirect_out(t_shell *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_OUT (>) at token %d\n", token_idx);
    // TODO: Implement output redirection logic
    
}
