/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:37:02 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void init_idx(t_shell *shell, char **envp)
{
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->doc = -1;
	shell->fd_in  = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->env = set_linked_path(envp);    // Convert to t_list format
	// Removed parser initialization since t_shell has no parser field
	//init_all_t_arr(shell);
}

void	init_minishell(t_minishell *shell, char **envp)
{
	if (!shell || !envp)
		return;

	// Ne PAS faire memset ici si l'environnement est déjà initialisé dans start_minishell

	shell->args = NULL;
	shell->parser.input = NULL;
	shell->exit_status = 0;

	// Initialisation du parser
	init_idx(&shell->parser, envp);
	init_all_t_arr(shell);
}

/*
t_env *init_env(char **envp)
{
	t_env *head = NULL;

	int i = 0;
	while (envp[i])
	{
		char *eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			t_env *new = malloc(sizeof *new);
			if (!new)
				return NULL;

			new->key = ft_substr(envp[i], 0, eq - envp[i]);
			new->value = ft_strdup(eq + 1);
			new->next = head;
			head = new;
		}
		i++;
	}
	return head;
}*/

/*loop principal dans mainloop.c*/

/*int	start_minishell(t_minishell *shell, char **envp)
{
	if (!shell || !envp)
		return (0);
	
	// Initialize the minishell structure
	memset(shell, 0, sizeof(t_minishell));
	init_idx(&shell->parser, envp);
	init_signals(); // Initialize signal handlers
	shell->env = init_envp(envp);
    if (!shell->env)
    {
        printf("Erreur : échec d'initialisation de l'environnement\n");
        return (1);
    }
	init_minishell(shell, envp);
	looping(shell);
	// Here,
	//	you can add any additional initialization steps needed for your minishell
	// Additional initialization steps can be added here
	// For example, setting up signal handlers, initializing the AST, etc.
	free_minishell(shell);
	return (1); // Return 1 on success
}*/
int	start_minishell(t_minishell *shell, char **envp)
{
	if (!shell || !envp)
		return (0);

	memset(shell, 0, sizeof(t_minishell));         // ici c'est ok car tu n'as rien encore mis dans shell
	//shell->env = init_env(envp);                  // initialise ton env
	shell->parser.env = set_linked_path(envp);
	if (!shell->parser.env)
	{
		printf("Erreur : échec d'initialisation de l'environnement\n");
		return (1);
	}

	init_signals();                                // gestion des signaux
	init_minishell(shell, envp);                   // initialise le reste (parser, etc)
	looping(shell);                                // boucle principale

	free_minishell(shell);                         // nettoyage
	return (1);                                     // succès
}
