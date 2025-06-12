#ifndef ENV_H
# define ENV_H

#include "minishell.h"

typedef struct s_env
{
    char            *key;   // nom de la variable d'env
    char            *value; // valeur de la variable
    struct s_env    *next;  // maillon suivant
}   t_env;

// Fonctions pour créer et gérer la liste (header ici, code dans env.c)
t_env   *init_env(char **envp);
void    free_env(t_env *env);
void    print_env(t_env *env); // affichage de la liste pour debug

#endif
/*
why ?
    -> manipuler l’environnement, le modifier (export, unset…), et faire des expansions ($VAR).

    -> liste chaînée permet de facilement ajouter/supprimer/chercher une variable d’environnement.
*/