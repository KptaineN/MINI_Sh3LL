/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:22:51 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:23:12 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// Fonctions de gestion de l'env
t_env				*init_env(char **envp);
void				free_env(t_env *env);
void				print_env(t_env *env);
char				*get_env_value(t_env *env, const char *name);
// ... autres prototypes liés à l'env
#endif

/*
why ?
	-> manipuler l’environnement, le modifier (export, unset…),
		et faire des expansions ($VAR).

	-> liste chaînée permet de facilement ajouter/supprimer/chercher une variable d’environnement.
*/