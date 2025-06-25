/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/25 17:37:26 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int	looping(t_minishell *shell)
{
	while (1)
	{
		shell->input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
		if (!shell->input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(shell->input) > 0)
		{
			add_history(shell->input);
			//parse_input(shell);     // À écrire : transforme en AST
			//execute_command(shell); // À écrire : exécute l’AST
		}
		free(shell->input);
		shell->input = NULL;
	}
	return (0);
}*/
int	looping(t_minishell *shell)
{
while (1)
{
	shell->input = readline("ᕕ( ᐛ )ᕗ minishell$");
	if (!shell->input)
		{
			write(1, "exit\n", 5);
			exit_shell(shell, shell->exit_status);
		}
	if (ft_strlen(shell->input) > 0)
	{
		add_history(shell->input);

		// BYPASS DU PARSING : AST fake minimal
		t_ast *fake = malloc(sizeof(t_ast));
		fake->type = NODE_COMMAND;
		fake->args = ft_split(shell->input, ' '); // naïf
		fake->filename = NULL;
		fake->left = NULL;
		fake->right = NULL;

		shell->ast = fake;

		execute_command(shell);

		free_tab(fake->args); // à créer si besoin
		free(fake);
	}
	free(shell->input);
	shell->input = NULL;
}
return (0);
}


/*
print_prompt : optionnel, tu peux mettre une couleur,
	ou afficher un état du shell (mais readline gère déjà un prompt simple).

readline("minishell$ ") : lit la ligne de l’utilisateur.

if (!shell->input) : détecte EOF (CTRL+D) ⇒ on sort proprement.

ft_strlen(shell->input) > 0 : n’ajoute à l’historique,
	ne parse et n’exécute que si ce n’est pas une ligne vide.

free : toujours, après chaque ligne lue,
	tu la libères pour éviter un leak à chaque boucle.

La boucle principale attend l’utilisateur, récupère sa ligne, vérifie EOF,
	historise, parse, exécute, libère.

Toujours free l’input, même si elle est vide ou n’a pas servi.

Organisation modulaire : tu peux ensuite faire évoluer parse_input et execute_command tranquillement.
*/