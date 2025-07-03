/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/03 01:56:20 by nkiefer          ###   ########.fr       */
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

void ft_free_array(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i]) free(arr[i++]);
    free(arr);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void free_tab(char **tab)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_t_arr(t_arr *array)
{
	if (!array)
		return;
	if (array->arr)
	{
		for (int i = 0; i < array->len; i++)
			free(array->arr[i]);
		free(array->arr);
	}
	free(array);
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

 //* Libère toute la mémoire de la structure minishell.
 //* À compléter selon l'évolution de ta structure.

 void	free_minishell(t_minishell *shell)
{
	if (!shell)
        return;
    // Libère la ligne d'entrée utilisateur
    // input et args sont déjà libérés dans cleanup_after_exec
    // S'il reste un input en cas d'erreur, free ici :
    if (shell->input)
        free(shell->input);
		// Libère le tableau d'arguments (ft_free_array est un helper type free_split)
    if (shell->args)
        ft_free_array(shell->args);

    // AST : peut être NULL si déjà nettoyée 
	// Libère l'AST
    if (shell->ast)
    {
        free_ast(shell->ast);
        shell->ast = NULL;
    }

    // Env : idem, free ici et nullifier
	 // Libère la liste chaînée des variables d'environnement

    if (shell->env)
    {
        free_env(shell->env);
        shell->env = NULL;
    }

    // Tout autre champ à libérer…

	 // (OPTIONNEL selon évolution de la struct)
	 // if (shell->env_list)
	 //     free_env_list(shell->env_list);
	 // (OPTIONNEL plus tard) : libère l'historique ou d'autres ressources globales
	 // free_history(shell->history);
	 // (OPTIONNEL plus tard) : libère des fd ou autres buffers
	 // if (shell->some_fd != -1) close(shell->some_fd);
	 // (OPTIONNEL plus tard) : libère des structures temporaires
	 // if (shell->tmp_data) free_tmp_data(shell->tmp_data);
/*
	Quand tu ajouteras un nouveau champ à t_minishell, par exemple :

	 un buffer (char *buffer)

	 une nouvelle liste (t_list *jobs)

	 un tableau de file descriptors (int *fd_tab)

Ajoute la ligne de libération dans free_minishell comme ceci :

if (shell->buffer)
	free(shell->buffer);

if (shell->jobs)
	free_job_list(shell->jobs);

if (shell->fd_tab)
	free(shell->fd_tab);
 */
	 // ... ajoute ici tout ce que tu ajoutes dans la struct plus tard !
}


// Fichier : exit_utils.c par exemple
void	exit_shell(t_minishell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history(); // nettoie readline
	exit(exit_code);
}
