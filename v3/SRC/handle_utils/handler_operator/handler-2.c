#include "../../../include/minishell.h"


int handle_pipe(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling PIPE (|) at token %d\n", token_idx);
    // TODO: Implement pipe logic
    return (0);
}

int handle_redirect_in(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_IN (<) at token %d\n", token_idx);
    // TODO: Implement input redirection logic
    return (0);
}

int handle_redirect_out(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_OUT (>) at token %d\n", token_idx);
    // TODO: Implement output redirection logic
    return (0);
}
