#ifndef ECHO_H
#define ECHO_H

#include "../../../include/minishell.h"

int builtin_echo(char **args, t_minishell *sh);
char *get_dollar_value(const char *arg, int *pos, t_minishell *sh);
char *replace_variables(const char *arg, t_minishell *sh);

#endif
