/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:23 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/16 16:03:27 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Ex : cmd_line = "ls -l | grep .c | wc -l > out.txt"

t_ast	*parse_line_to_ast(const char *cmd_line)
{
	// Étape 1 : split sur les pipes, gérant les quotes avec tes helpers
	// --> ["ls -l", "grep .c", "wc -l > out.txt"]
	// Étape 2 : pour chaque portion,
	//split sur espaces(en gérant quotes) pour args
	// Étape 3 : pour chaque ">", "<", ">>", construis un noeud AST redir
	// Enfin, assemble un arbre binaire :
	//         PIPE
	//       /      \
    //   PIPE      CMD("wc -l > out.txt")
	//    /    \
    //CMD("ls -l") CMD("grep .c")

}
/*
À partir de la liste de tokens (créée par le lexer), construire une structure en arbre binaire représentant la logique de la ligne de commande.

Chaque nœud de l’AST contient un token opérateur (comme |, >, etc.), et ses enfants contiennent soit :

    une autre commande

    un autre opérateur

Fonction principale : t_ast *parse_line_to_ast(t_token *tokens);

Elle prend la liste chaînée de t_token et retourne l’AST.

Il faut parser en suivant une priorité d'opérateurs, généralement :

1. Pipe    → `|`
2. Redirections → `>`, `<`, `>>`, `<<`
3. Commandes (mots) → feuilles

L’approche classique :

    Trouver l’opérateur le plus prioritaire (le moins prioritaire visuellement)

    Découper la liste à cet opérateur (comme au centre d’un arbre)

    Créer un nœud AST avec ce token

    Appliquer récursivement à gauche et à droite

	Code simplifié de ast.c (esquisse)

#include "minishell.h"

t_ast *create_ast_node(t_token *token)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_token *find_operator(t_token *tokens, t_token_type type)
{
	while (tokens)
	{
		if (tokens->type == type)
			return tokens;
		tokens = tokens->next;
	}
	return NULL;
}

t_ast *parse_line_to_ast(t_token *tokens)
{
	t_token *op;

	// Étape 1 : chercher un PIPE
	op = find_operator(tokens, PIPE);
	if (op)
	{
		t_ast *node = create_ast_node(op);
		op->type = -1; // marqué comme utilisé
		node->left = parse_line_to_ast(tokens);
		node->right = parse_line_to_ast(op->next);
		return node;
	}

	// Étape 2 : pas d’opérateur ? → feuille (commande)
	if (tokens)
	{
		t_ast *node = create_ast_node(tokens);
		return node;
	}
	return NULL;
}

    ⚠️ Ce code est très simplifié. Tu devras :

    gérer les priorités d’opérateurs

    gérer les redirections

    dupliquer les chaînes pour ne pas perdre les tokens

    éviter les modifications destructives (op->type = -1, à remplacer)

🧪 Exemple de test à faire

char *input = "ls -l | grep .c | wc -l";
t_token *tokens = lexer(input);
t_ast *ast = parse_line_to_ast(tokens);
print_ast(ast);

🔧 À faire aussi

    Une fonction void free_ast(t_ast *root) pour éviter les fuites mémoire

    Une fonction void print_ast(t_ast *root, int level) pour afficher visuellement l’arbre

📌 Résumé
Élément	Rôle
parse_line_to_ast	Construit récursivement l’AST depuis les tokens
create_ast_node	Alloue un nœud d’AST
ast->left / ast->right	Représente les sous-commandes avant/après un opérateur

*/

#include "../../include/minishell.h"

static char	**dup_args(char **args)
{
	int		count = 0;
	char	**copy;

	while (args && args[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	int i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

t_ast *init_redirection_node(t_node_type type, const char *filename, t_ast *child)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->filename = ft_strdup(filename);
	node->left = child;
	node->right = NULL;
	return (node);
}


t_ast	*init_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
