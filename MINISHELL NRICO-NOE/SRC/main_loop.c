/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/12 16:24:18 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	looping(t_minishell *shell)
{
	while (1)
	{
		shell->input = readline("minishell$ ");
		if (!shell->input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(shell->input) > 0)
		{
			add_history(shell->input);
			parse_input(shell);     // À écrire : transforme en AST
			execute_command(shell); // À écrire : exécute l’AST
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