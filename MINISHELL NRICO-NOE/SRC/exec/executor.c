/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:35:42 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Pour lancer un pipeline complet (même si c'est juste une commande)
void	execute_command(t_ast *ast, t_env *env)
{
	execute_ast_pipeline(ast, env, STDIN_FILENO);
}

void	execute_ast(t_ast *ast, t_env *env)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
		execute_ast_pipeline(ast, env, STDIN_FILENO);
	else
		exec_cmd_node(ast, env, STDIN_FILENO);
}

/*
Regarder le contenu de ton AST (arbre de commandes que tu as construit en parsant l’input).

Décider : est-ce que c’est…

	Un builtin ? (commande interne du shell comme cd, echo, export…)

	Un pipeline ? (plusieurs commandes reliées par des pipes,
		ex : ls | grep .c | wc -l)

	Une commande simple ? (juste un binaire sans pipe, ex : ls -l)

Appeler la fonction adaptée pour gérer le cas :

	builtin : Exécution spéciale (souvent SANS fork)

	pipeline : Exécution pipex-style (fork + pipe entre chaque)

	simple : Juste fork + execve, redirections éventuelles
*/
void	execute_command(t_minishell *shell)
{
	if (!shell->ast)
		return ;
	if (is_builtin(shell->ast))
		execute_builtin(shell, shell->ast);
	else if (is_pipeline(shell->ast))
		execute_pipeline(shell->ast, shell->env);
	else
		execute_simple(shell->ast, shell->env);
}
