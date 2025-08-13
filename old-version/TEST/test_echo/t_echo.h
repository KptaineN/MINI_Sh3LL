#ifndef T_ECHO_H
#define T_ECHO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "LIBFT/libft.h"

// ===== STRUCTURES =====
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;

typedef struct s_shell {
    t_list *env;
    int     exit_status;
} t_shell;

// ===== PROTOTYPES =====
int ft_echo(t_shell *shell, char **argv);
int builtin_echo(t_shell *shell, char **argv);
char *find_env_value(t_list *env, const char *key);
char *get_dollar_value(const char *arg, int *pos, t_shell *sh);
char *replace_variables(const char *arg, t_shell *sh);

#endif
