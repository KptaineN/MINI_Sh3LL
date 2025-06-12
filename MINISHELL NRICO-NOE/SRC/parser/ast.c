/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:23 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:25:25 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Ex : cmd_line = "ls -l | grep .c | wc -l > out.txt"

t_ast	*parse_line_to_ast(const char *cmd_line)
{
	// Étape 1 : split sur les pipes, gérant les quotes avec tes helpers
	// --> ["ls -l", "grep .c", "wc -l > out.txt"]
	// Étape 2 : pour chaque portion,
	split sur espaces(en gérant quotes) pour args
	// Étape 3 : pour chaque ">", "<", ">>", construis un noeud AST redir
	// Enfin, assemble un arbre binaire :
	//         PIPE
	//       /      \
    //   PIPE      CMD("wc -l > out.txt")
	//    /    \
    //CMD("ls -l") CMD("grep .c")
}
