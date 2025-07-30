#ifndef ECHO_H
#define ECHO_H

#include "../../../include/minishell.h"
#include "../../../include/parsking.h"
#include "../../../include/struct.h"
// Au début de ton header (ex : echo.h ou export.h)



//int builtin_echo(t_shell *parser, t_token *token);
int builtin_echo(t_shell *shell, t_token *token);

char *get_dollar_value(const char *arg, int *pos, t_shell *sh);
char *replace_variables(const char *arg, t_shell *sh);

#endif
