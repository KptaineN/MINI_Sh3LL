/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:30 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/24 13:41:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// test

/*Tu as déjà une version simplifiée de parse_line_to_ast() qui :

    alloue un nœud t_ast

    suppose qu’il n’y a qu’une commande simple sans redirection ni pipe

    découpe input avec ft_split(input, ' ')

C’est un bon point de départ, mais ce n’est pas encore un vrai parser, car il ne prend pas en compte :

    les pipes |

    les redirections <, >, >>, <<

    les quotes

    l’ordre d’exécution*/
/*t_ast	*parse_line_to_ast(const char *input)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->args = ft_split(input, ' '); // Pas gestion des quotes ni pipes ici,
	//	juste split simple
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}*/


	// Exemples : découpe sur les pipes (à améliorer ensuite)
	// ["ls -l", "grep .c"]

/*
 * parse_input : Tokenize input, parse AST, puis éventuellement exécute.
 * - Ne fait QUE parser (laisse la responsabilité de l’exécution ailleurs !)
 */
//void	parse_input(t_minishell *shell)
//{
	//if (!shell || !shell->input)
	//	return;

	// 1. Tokenization (optionnel si tu veux lexer d’abord)
	// t_token *tokens = lexer(shell->input);
	// shell->ast = parse_line_to_ast(tokens);

	// 2. Version minimaliste : parser direct sur la string (sans lexer pour l’instant)
	//shell->ast = parse_line_to_ast(shell->input);

	// 3. Optionnel : debug AST
	// print_ast(shell->ast, 0);
//}


/*

Tu n'utilises plus la ligne brute (const char *input), mais la liste de tokens que le lexer a produit :

t_ast *parse_line_to_ast(t_token *tokens);

📦 Exemple d'implémentation de parser.c

#include "minishell.h"

t_ast *create_cmd_node(t_token *start)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return NULL;
	node->type = NODE_COMMAND;

	int count = 0;
	t_token *tmp = start;
	while (tmp && tmp->type == WORD)
	{
		count++;
		tmp = tmp->next;
	}
	node->args = malloc(sizeof(char *) * (count + 1));
	tmp = start;
	for (int i = 0; i < count; i++)
	{
		node->args[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	node->args[count] = NULL;
	node->left = NULL;
	node->right = NULL;
	node->filename = NULL;
	return node;
}

t_ast *parse_line_to_ast(t_token *tokens)
{
	t_token *current = tokens;

	// Chercher un PIPE
	while (current)
	{
		if (current->type == PIPE)
		{
			t_ast *node = malloc(sizeof(t_ast));
			node->type = NODE_PIPE;
			node->left = parse_line_to_ast(tokens);
			node->right = parse_line_to_ast(current->next);
			node->args = NULL;
			node->filename = NULL;
			return node;
	for (int i = 0; i < count; i++)
	{
		node->args[i] = ft_strdup(tmp->value);
		}
		current = current->next;
	}
	// Pas de pipe → commande simple
	return create_cmd_node(tokens);
}

🧪 Test dans parse_input()

void parse_input(t_minishell *shell)
{
	t_token *tokens = lexer(shell->input);
	shell->ast = parse_line_to_ast(tokens);
}

🧹 À ajouter

    free_ast(t_ast *ast) : pour éviter les fuites

    print_ast(t_ast *ast, int level) : debug visuel

📌 Résumé
Fichier	Fonction	Rôle
parser.c	parse_line_to_ast(t_token *tokens)	génère un AST à partir des tokens
create_cmd_node()	crée une feuille (commande simple)	
NODE_PIPE	type d’AST pour gérer les `	`
NODE_COMMAND	commande sans opérateurs	
args	tableau de chaînes (char **) pour les commandes


y a ca aussi #include "minishell.h"
#include <stdio.h>
*/
static char **split_on_pipes(const char *input)
{
	return ft_split(input, '|');
}
/*
void free_strtab(char **tab)
{
	int i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

static t_ast *parse_redirection(char **args)
{
	t_ast *cmd = init_command_node(args);
	if (!cmd)
		return NULL;

	for (int i = 0; args[i]; i++)
	{
		t_node_type type;
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>") ||
			!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
		{
			if (!args[i + 1])
				return cmd; // Erreur : pas de fichier après l'opérateur

			if (!ft_strcmp(args[i], ">"))
				type = NODE_REDIR_OUT;
			else if (!ft_strcmp(args[i], ">>"))
				type = NODE_REDIR_APPEND;
			else if (!ft_strcmp(args[i], "<"))
				type = NODE_REDIR_IN;
			else
				type = NODE_HEREDOC;

			t_ast *redir = init_redirection_node(type, args[i + 1], cmd);

			// Supprime les arguments de redirection
			free(args[i]);
			free(args[i + 1]);
			args[i] = NULL;
			args[i + 1] = NULL;

			return redir;
		}
	}
	return cmd;
}
*/
t_ast *parse_line_to_ast(const char *input)
{
	char **segments = split_on_pipes(input);
	t_ast *current = NULL;
	t_ast *right = NULL;

	if (!segments)
		return NULL;

	int i = 0;
	current = parse_redirection(ft_split(segments[i], ' '));
	i++;
	while (segments[i])
	{
		t_ast *pipe_node = init_ast_node(NODE_PIPE);
		right = parse_redirection(ft_split(segments[i], ' '));

		pipe_node->left = current;
		pipe_node->right = right;
		current = pipe_node;
		i++;
	}
	free_strtab(segments);
	return current;
}

/*
parse_line_to_ast() doit maintenant prendre en entrée les shell->parser.tokens et token_count, pas un char *input.

Si tu veux que je t’aide à écrire le nouveau parse_line_to_ast(t_minishell *shell), je peux te le faire.

Pense à libérer parser.parsed_args et parser.tokens dans free_minishell
*/
void	parse_input(t_minishell *shell)
{
	if (!shell || !shell->input)
		return;

	// Nettoyage de l'ancien AST si besoin
	if (shell->ast)
		free_ast(shell->ast);

	// Nettoyage des anciens tokens / arrays si besoin
	if (shell->parser.parsed_args)
		free_t_arr(shell->parser.parsed_args); // à écrire
	if (shell->parser.tokens)
		free(shell->parser.tokens); // si besoin free all_tokens

	// Phase 1 : split en "arguments" simples (respect des quotes)
	shell->parser.parsed_args = custom_split(shell->input);
	if (!shell->parser.parsed_args)
		return;

	// Phase 2 : attribution des types + sous-tokens
	attribute_token_type(&shell->parser);

	// Phase 3 : construction de l'AST à partir des tokens
	shell->ast = parse_line_to_ast(shell);
	if (!shell->ast)
	{
		ft_putendl_fd("parse error", STDERR_FILENO);
		return;
	}

	print_ast(shell->ast, 0); // debug
	execute_command(shell); // Exécution à partir de l’AST
}

