/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:27:59 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	free_ast(t_ast *ast)
{
	// This function should free the AST structure
	// For now, we will just print a message for debugging
	if (ast)
	{
		printf("Freeing AST...\n");
		// Here you would typically free the AST nodes
		// free_ast_nodes(ast);
	}
}
void	clean_exit(char **cmd_args, char *msg, int code)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (cmd_args)
		ft_free_split(cmd_args);
	exit(code);
}
