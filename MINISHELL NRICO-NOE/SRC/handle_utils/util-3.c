/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/16 16:13:59 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	free_args(char **args)
{
	int	i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	parse_input(t_minishell *shell)
{
	// This function should parse the input and build the AST
	// For now, we will just print the input for debugging
	if (shell->input)
	{
		printf("Parsing input: %s\n", shell->input);
		// Here you would typically call a function to build the AST
		// shell->ast = build_ast(shell->input);
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return;

	// Libère récursivement les sous-arbres
	free_ast(node->left);
	free_ast(node->right);

	// Libère le tableau d'arguments (pour les commandes)
	free_args(node->args);

	// Libère le nom de fichier (pour les redirections)
	if (node->filename)
		free(node->filename);

	// Libère le nœud lui-même
	free(node);
}
void	clean_exit(char **cmd_args, char *msg, int code)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (cmd_args)
		ft_free_split(cmd_args);
	exit(code);
}
