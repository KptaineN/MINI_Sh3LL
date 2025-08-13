#include "t_echo.h"

int ft_echo(t_shell *shell, char **argv)
{
    return builtin_echo(shell, argv);
}

// Petit utilitaire pour print un séparateur test
void print_test(const char *desc) {
    printf("\n=== TEST: %s ===\n", desc);
}

int main(void) {

   /**/ t_shell shell;
    shell.env = NULL;
    shell.exit_status = 42;
    // Tableaux de tests (chacun = argv complet à passer à ft_echo)
    char *t1[]  = {"echo", NULL};
    char *t2[]  = {"echo", "test", NULL};
    char *t3[]  = {"echo", "test1", "test2", NULL};
    char *t4[]  = {"echo", "-n", "test", NULL};
    char *t5[]  = {"echo", "-n", "-n", "test", NULL};
    char *t6[]  = {"echo", "-nnnnn", "test", NULL};
    char *t7[]  = {"echo", "-n", NULL};
    char *t8[]  = {"echo", "", NULL};
    char *t9[]  = {"echo", "a    b", NULL};
    char *t10[] = {"echo", "'abc'", NULL};
    char *t11[] = {"echo", "\"abc\"", NULL};
    char *t12[] = {"echo", "\"a   b\"", NULL};
    char *t13[] = {"echo", "\"\"", "\"\"", NULL};
    char *t14[] = {"echo", "   a  b  c   ", NULL};
    char *t15[] = {"echo", "a", "b", "c", NULL};
    char *t16[] = {"echo", "a", "    b     ", "c", NULL};
    // Tu peux ajouter des cas variables si ton echo les gère :
    char *t17[] = {"echo", "$USER", NULL};
    char *t18[] = {"echo", "\"$USER\"", NULL};
    char *t19[] = {"echo", "'$USER'", NULL};

    struct { const char *desc; char **args; } tests[] = {
        {"echo", t1},
        {"echo test", t2},
        {"echo test1 test2", t3},
        {"echo -n test", t4},
        {"echo -n -n test", t5},
        {"echo -nnnnn test", t6},
        {"echo -n", t7},
        {"echo \"\"", t8},
        {"echo \"a    b\"", t9},
        {"echo 'abc'", t10},
        {"echo \"abc\"", t11},
        {"echo \"a   b\"", t12},
        {"echo \"\" \"\"", t13},
        {"echo \"   a  b  c   \"", t14},
        {"echo a b c", t15},
        {"echo a    b     c", t16},
        {"echo $USER", t17},
        {"echo \"$USER\"", t18},
        {"echo '$USER'", t19},
    };

    int nb_tests = sizeof(tests)/sizeof(tests[0]);
    for (int i = 0; i < nb_tests; i++) 
    {
            print_test(tests[i].desc);
            ft_echo(&shell, tests[i].args);
            printf("[END]\n");
        }
    return 0;
}
